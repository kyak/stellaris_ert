Simulink (Embedded Coder) Target for TI Stellaris LaunchPad
=============

Summary:

TI Stellaris LaunchPad (http://www.ti.com/stellaris-launchpad-b) is a low-cost
development board based on ARM Cortex-M4F.

Simulink (http://www.mathworks.com/products/simulink) is a leading environment
for multidomain simulation and Model-Based Design.

Embedded Coder (http://www.mathworks.com/products/embedded-coder) allows you to
generate C code and deploy your algorithms to target hardware.

Installation:

1) Windows/Linux: Have Code Composer Studio 5.3 installed (http://processors.wiki.ti.com/index.php/Download_CCS).

2) Windows/Linux: Have StellarisWare installed (http://www.ti.com/tool/SW-EK-LM4F120XL).
You don't have to download the complete StellarisWare package.
"StellarisWare for the Stellaris LM4F120 LaunchPad Evaluation Board" is enough.

3) Linux only: have lm4flash installed (https://github.com/utzig/lm4tools/tree/master/lm4flash).
This is needed to flash Stellaris programmatically under Linux.
For some reason, dss.sh doesn't work for me, though i can flash fine from CCS itself.

Make sure your toolchain is working (build and download some test project, check connection)
before you proceed!

4) Make sure you have a working/supported host compiler (http://www.mathworks.com/support/compilers/R2012b/index.html) by running
        
        mex -setup
in MATLAB.

5) Extract this package somewhere. Make sure there are no spaces/non-ASCII characters in path (just in case).

6) Within MATLAB, 'cd' to the directory containing stellaris_setup.m and run this script.

You should be good to go.

What this package already has:

- Standalone execution on target (driven by ISR)
- Simulink library blocks for:
        
        * GPIO
        * Push Buttons
        * UART Read/Write

What this package would like to have:

- Simulink library blocks for:

        * Built-in temperature sensor
        * Generic ADC, PWM...
- Execution in PIL mode
- PIL mode profiling
- More documentation
- External Mode support