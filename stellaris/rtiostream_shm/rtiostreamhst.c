//#define DEBUG

#ifdef _WIN32
#define RTIOSTREAMAPI __declspec( dllexport )
#endif

#include "rtiostream.h"
#include "MLink.h"
#include <string.h>

#ifdef DEBUG
#include "mex.h"
#endif

#ifdef _WIN32
#include <Windows.h>
#define SLEEP_SET_OBJ Sleep(7);
#else
#include <unistd.h>
#define SLEEP_SET_OBJ usleep(7000);
#endif

#define BUFSIZE 2055
/* Send buffer on target */
static volatile uint8_t  buf_snd[BUFSIZE] = {0};
/* Receive buffer on target */
static volatile uint8_t  buf_rcv[BUFSIZE] = {0};
/* Flag to indicate one of the following:
 * - Target currently reads from the receive buffer and host must not write there.
 * - Host currently writes to the receive buffer and target must not read from there. */
static uint32_t sem_snd          =  0;
/* Flag to indicate one of the following:
 * - Host currently reads from the send buffer and target must not write there.
 * - Target currently writes to the send buffer and host must not read from there. */
static uint32_t sem_rcv          =  0;
/* Position in target's receive buffer */
static uint32_t out_rcv          =  0;
/* Position in host's send buffer */
static uint32_t in_rcv           =  0;
/* Position in target's send buffer */
static uint32_t in_snd           =  0;
/* Position in host's receive buffer */
static uint32_t out_snd          =  0;

/* Initialize rtIOStream */
RTIOSTREAMAPI int rtIOStreamOpen(int argc, void *argv[])
{
    int result, streamID, count = 0;
    char * ipaddr = "10.10.1.1";
    /* Initialize flags to avoid weird behaviour when this library is reused */
    sem_snd          =  0;
    sem_rcv          =  0;
    out_rcv          =  0;
    in_rcv           =  0;
    in_snd           =  0;
    out_snd          =  0;

    /* Parse arguments */
    while(count < argc) {
        const char *option = (char *)argv[count];
        count++;
        if (option != NULL) {
            if ((strcmp(option, "-ipaddr") == 0) && (count != argc)) {
                ipaddr = (char *)argv[count];
                count++;
                argv[count-2] = NULL;
                argv[count-1] = NULL;
            }
        }
    }
    result = mlink_connect(ipaddr, 4343, &streamID);
    if (result < 0) {
      return RTIOSTREAM_ERROR;
    } else {
      return streamID;
    }
}

/* Read data from rtIOStream */
RTIOSTREAMAPI int rtIOStreamRecv(
        int      streamID,  // A handle to the stream that was returned by a previous call to rtIOStreamOpen.
        void   * dst,       // A pointer to the start of the buffer where received data must be copied.
        size_t   size, 	    // Size of data to copy into the buffer. For byte-addressable architectures,
                            // size is measured in bytes. Some DSP architectures are not byte-addressable.
                            // In these cases, size is measured in number of WORDs, where sizeof(WORD) == 1.
        size_t * sizeRecvd) // The number of units of data received and copied into the buffer dst (zero if no data was copied).
{
    uint8_t *ptr = (uint8_t *)dst;
    uint8_t result = 0;
#ifdef DEBUG
    int i;
#endif
    *sizeRecvd = 0U;
    
#ifdef DEBUG
    printf("Commanded to receive %d bytes from target...\n",size);
#endif
    
    /* Check if target is sending right now */
    result = mlink_get_obj(&streamID, "sem_snd", &sem_snd, sizeof(sem_snd));
    if (result < 0)
        return RTIOSTREAM_ERROR;
#ifdef DEBUG
    printf("Checking if target is sending right now...\n");
#endif
    if (sem_snd > 0) {
#ifdef DEBUG
        printf("Target is sending right now, sem_snd is %d\n",sem_snd);
#endif
        /* Return immediately if target is sending */
        return RTIOSTREAM_NO_ERROR;
    } else {
#ifdef DEBUG
        printf("Target is NOT sending, sem_snd is %d\n",sem_snd);
#endif
        /* Host starts reading, set semaphore */
        sem_snd = 1;
        result = mlink_set_obj(&streamID, "sem_snd", &sem_snd, sizeof(sem_snd));
        if (result < 0)
            return RTIOSTREAM_ERROR;
        SLEEP_SET_OBJ
#ifdef DEBUG
        printf("Setting sem_snd to %d\n",sem_snd);
#endif
        /* Read the actual in/out positions in target's send buffer */
        result = mlink_get_obj(&streamID, "in_snd", &in_snd, sizeof(in_snd));
        if (result < 0)
            return RTIOSTREAM_ERROR;
        result = mlink_get_obj(&streamID, "out_snd", &out_snd, sizeof(out_snd));
        if (result < 0)
            return RTIOSTREAM_ERROR;
#ifdef DEBUG
        printf("The actual in/out positions in target's send buffer: %d/%d\n",in_snd,out_snd);
#endif
        /* Get the data from target */
        result = mlink_get_obj(&streamID, "buf_snd", &buf_snd, sizeof(buf_snd));
        if (result < 0)
            return RTIOSTREAM_ERROR;
        /* Read the requested 'size' number of bytes from buffer */
        while (*sizeRecvd < size) {
            if (in_snd == out_snd) {
#ifdef DEBUG
                printf("Buffer Empty - nothing to get.\n");
#endif
                /* Buffer Empty - nothing to get */
                break;
            }
            *ptr++ = buf_snd[out_snd];
            (*sizeRecvd)++;
            out_snd = (out_snd + 1) % BUFSIZE;
        }
    }
#ifdef DEBUG
    printf("Received size: %d\n",*sizeRecvd);
    printf("in/out positions in target's send buffer after receive: %d/%d\n",in_snd,out_snd);
#endif
    /* Update out position in target's send buffer */
    result = mlink_set_obj(&streamID, "out_snd", &out_snd, sizeof(out_snd));
    if (result < 0)
        return RTIOSTREAM_ERROR;
    SLEEP_SET_OBJ
    /* Host finished reading, unset semaphore */
    sem_snd = 0;
    result = mlink_set_obj(&streamID, "sem_snd", &sem_snd, sizeof(sem_snd));
    if (result < 0)
        return RTIOSTREAM_ERROR;
    SLEEP_SET_OBJ
#ifdef DEBUG
    printf("Setting sem_snd to %d\n",sem_snd);
    printf("Rcvd data: ");
    for (i = out_snd_entry-*sizeRecvd; i<out_snd_entry; i++) {
        printf("%0x ",buf_snd[i]);
    }
    printf("\n\n");
#endif
    return RTIOSTREAM_NO_ERROR;
}

/* Write data to rtIOStream */
RTIOSTREAMAPI int rtIOStreamSend(
        int          streamID,
        const void * src,
        size_t       size,
        size_t     * sizeSent)
{
    uint8_t *ptr = (uint8_t *)src;
    uint8_t result = 0;
#ifdef DEBUG
    int i;
#endif
    *sizeSent = 0U;
    
#ifdef DEBUG
    printf("Commanded to send %d bytes to target...\n",size);
#endif
    
    /* Check if target is reading right now */
    result = mlink_get_obj(&streamID, "sem_rcv", &sem_rcv, sizeof(sem_rcv));
    if (result < 0)
        return RTIOSTREAM_ERROR;
#ifdef DEBUG
    printf("Checking if target is reading right now...\n");
#endif
    if (sem_rcv > 0) {
#ifdef DEBUG
        printf("Target is reading right now, sem_rcv is %d\n",sem_rcv);
#endif
        /* Return immediately if target is reading */
        return RTIOSTREAM_NO_ERROR;
    } else {
#ifdef DEBUG
        printf("Target is NOT reading, sem_rcv is %d\n",sem_rcv);
#endif
        /* Host starts sending, set semaphore */
        sem_rcv = 1;
        result = mlink_set_obj(&streamID, "sem_rcv", &sem_rcv, sizeof(sem_rcv));
        if (result < 0)
            return RTIOSTREAM_ERROR;
        SLEEP_SET_OBJ
#ifdef DEBUG
        printf("Setting sem_rcv to %d\n",sem_rcv);
#endif
        /* Read the actual in/out positions in target's receive buffer */
        result = mlink_get_obj(&streamID, "in_rcv", &in_rcv, sizeof(in_rcv));
        if (result < 0)
            return RTIOSTREAM_ERROR;
        result = mlink_get_obj(&streamID, "out_rcv", &out_rcv, sizeof(out_rcv));
        if (result < 0)
            return RTIOSTREAM_ERROR;
#ifdef DEBUG
        printf("The actual in/out positions in target's receive buffer: %d/%d\n",in_rcv,out_rcv);
#endif
        /* Send the requested 'size' number of bytes to buffer */
        while (*sizeSent < size) {
            if (in_rcv == (( out_rcv - 1 + BUFSIZE) % BUFSIZE)) {
#ifdef DEBUG
                printf("Buffer Full - can't write.\n");
#endif
                /* Buffer Full - can't write */
                break;
            }
            buf_rcv[in_rcv] = *ptr++;
            (*sizeSent)++;
            in_rcv = (in_rcv + 1) % BUFSIZE;
        }
    }
#ifdef DEBUG
    printf("Sent size: %d\n",*sizeSent);
    printf("in/out positions in target's receive buffer after send: %d/%d\n",in_rcv,out_rcv);
#endif
    /* Send the buffer to the target */
    result = mlink_set_obj(&streamID, "buf_rcv", &buf_rcv, sizeof(buf_rcv));
    if (result < 0)
        return RTIOSTREAM_ERROR;
    SLEEP_SET_OBJ
    /* Update in position in target's receive buffer */
    result = mlink_set_obj(&streamID, "in_rcv", &in_rcv, sizeof(in_rcv));
    if (result < 0)
        return RTIOSTREAM_ERROR;
    SLEEP_SET_OBJ
    /* Host finished sending, unset semaphore */
    sem_rcv = 0;
    result = mlink_set_obj(&streamID, "sem_rcv", &sem_rcv, sizeof(sem_rcv));
    if (result < 0)
        return RTIOSTREAM_ERROR;
    SLEEP_SET_OBJ
#ifdef DEBUG
    printf("Setting sem_rcv to %d\n",sem_rcv);
    printf("Sent data: ");
    for (i = in_rcv_entry-*sizeSent; i<in_rcv_entry; i++) {
        printf("%0x ",buf_rcv[i]);
    }
    printf("\n\n");
#endif
    return RTIOSTREAM_NO_ERROR;
}

/* Close rtIOStream */
RTIOSTREAMAPI int rtIOStreamClose(int streamID)
{
    //int result;
    //Do we need to stop DSP?
    //result = mlink_dsp_stop(&streamID);
    mlink_disconnect(streamID);
    return RTIOSTREAM_NO_ERROR;
}
