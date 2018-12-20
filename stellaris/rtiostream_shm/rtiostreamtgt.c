//#define DEBUG

#include "rtiostream.h"
#include <stdint.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#define BUFSIZE 128
/* Send buffer on target */
volatile uint8_t  buf_snd[BUFSIZE] = {0};
/* Receive buffer on target */
volatile uint8_t  buf_rcv[BUFSIZE] = {0};
/* Flag to indicate one of the following:
 * - Target currently reads from the receive buffer and host must not write there.
 * - Host currently writes to the receive buffer and target must not read from there. */
volatile uint8_t sem_snd          =  0;
/* Flag to indicate one of the following:
 * - Host currently reads from the send buffer and target must not write there.
 * - Target currently writes to the send buffer and host must not read from there. */
volatile uint8_t sem_rcv          =  0;
/* Position in target's receive buffer */
volatile uint8_t out_rcv          =  0;
/* Position in host's send buffer */
volatile uint8_t in_rcv           =  0;
/* Position in target's send buffer */
volatile uint8_t in_snd           =  0;
/* Position in host's receive buffer */
volatile uint8_t out_snd          =  0;

void Timer0IntHandler(void) {
    /* This function is bogus and lives in startup_ccs.c */
}

/* Initialize rtIOStream */
int rtIOStreamOpen(int argc, void *argv[])
{
    /* Initialize flags here just in case */
    sem_snd          =  0;
    sem_rcv          =  0;
    out_rcv          =  0;
    in_rcv           =  0;
    in_snd           =  0;
    out_snd          =  0;

    return RTIOSTREAM_NO_ERROR;
}

/* Read data from rtIOStream */
int rtIOStreamRecv(
        int      streamID,  // A handle to the stream that was returned by a previous call to rtIOStreamOpen.
        void   * dst,       // A pointer to the start of the buffer where received data must be copied.
        size_t   size, 	    // Size of data to copy into the buffer. For byte-addressable architectures,
                            // size is measured in bytes. Some DSP architectures are not byte-addressable.
                            // In these cases, size is measured in number of WORDs, where sizeof(WORD) == 1.
        size_t * sizeRecvd) // The number of units of data received and copied into the buffer dst (zero if no data was copied).
{
    uint8_t *ptr = (uint8_t *)dst;
#ifdef DEBUG
    int i;
#endif
    *sizeRecvd = 0U;
    
#ifdef DEBUG
    printf("Commanded to receive %d bytes from host...\n",size);
#endif
#ifdef DEBUG
    printf("Checking if host is sending right now...\n");
#endif
    /* Check if host is sending right now */
    if (sem_rcv > 0) {
#ifdef DEBUG
        printf("Host is sending right now, sem_rcv is %d\n",sem_rcv);
#endif
        /* Return immediately if host is sending */
        return RTIOSTREAM_NO_ERROR;
    } else {
#ifdef DEBUG
        printf("Host is NOT sending, sem_rcv is %d\n",sem_rcv);
#endif
        /* Target starts reading, set semaphore */
        sem_rcv = 1;
#ifdef DEBUG
        printf("Setting sem_rcv to %d\n",sem_rcv);
#endif
#ifdef DEBUG
        printf("The actual in/out positions in target's receive buffer: %d/%d\n",in_rcv,out_rcv);
#endif
        /* Read the requested 'size' number of bytes from buffer */
        while (*sizeRecvd < size) {
            if (in_rcv == out_rcv) {
#ifdef DEBUG
                printf("Buffer Empty - nothing to get.\n");
#endif
                /* Buffer Empty - nothing to get */
                break;
            }
            *ptr++ = buf_rcv[out_rcv];
            (*sizeRecvd)++;
            out_rcv = (out_rcv + 1) % BUFSIZE;
        }
    }
#ifdef DEBUG
    printf("Received size: %d\n",*sizeRecvd);
    printf("in/out positions in target's receive buffer after receive: %d/%d\n",in_rcv,out_rcv);
#endif
    /* Target finished reading, unset semaphore */
    sem_rcv = 0;
#ifdef DEBUG
    printf("Setting sem_rcv to %d\n",sem_rcv);
    printf("Rcvd data: ");
    for (i = *sizeRecvd; i>0; i--) {
        printf("%0x ",*--ptr);
    }
    printf("\n\n");
#endif
    return RTIOSTREAM_NO_ERROR;
}

/* Write data to rtIOStream */
int rtIOStreamSend(
        int          streamID,
        const void * src,
        size_t       size,
        size_t     * sizeSent)
{
    uint8_t *ptr = (uint8_t *)src;
#ifdef DEBUG
    int i;
#endif
    *sizeSent = 0U;
    
#ifdef DEBUG
    printf("Commanded to send %d bytes to host...\n",size);
#endif
#ifdef DEBUG
    printf("Checking if host is reading right now...\n");
#endif
    /* Check if host is reading right now */
    if (sem_snd > 0) {
#ifdef DEBUG
        printf("Host is reading right now, sem_snd is %d\n",sem_snd);
#endif
        /* Return immediately if host is reading */
        return RTIOSTREAM_NO_ERROR;
    } else {
#ifdef DEBUG
        printf("Host is NOT reading, sem_snd is %d\n",sem_snd);
#endif
        /* Target starts sending, set semaphore */
        sem_snd = 1;
#ifdef DEBUG
        printf("Setting sem_snd to %d\n",sem_snd);
#endif
#ifdef DEBUG
        printf("The actual in/out positions in target's send buffer: %d/%d\n",in_snd,out_snd);
#endif
        /* Send the requested 'size' number of bytes to buffer */
        while (*sizeSent < size) {
            if (in_snd == (( out_snd - 1 + BUFSIZE) % BUFSIZE)) {
#ifdef DEBUG
                printf("Buffer Full - can't write.\n");
#endif
                /* Buffer Full - can't write */
                break;
            }
            buf_snd[in_snd] = *ptr++;
            (*sizeSent)++;
            in_snd = (in_snd + 1) % BUFSIZE;
        }
    }
#ifdef DEBUG
    printf("Sent size: %d\n",*sizeSent);
    printf("in/out positions in target's send buffer after send: %d/%d\n",in_snd,out_snd);
#endif
    /* Target finished sending, unset semaphore */
    sem_snd = 0;
#ifdef DEBUG
    printf("Setting sem_snd to %d\n",sem_snd);
    printf("Sent data: ");
    for (i = *sizeSent; i>0; i--) {
        printf("%0x ",*--ptr);
    }
    printf("\n\n");
#endif
    return RTIOSTREAM_NO_ERROR;
}

/* Close rtIOStream */
int rtIOStreamClose(int streamID)
{
    return RTIOSTREAM_NO_ERROR;
}
