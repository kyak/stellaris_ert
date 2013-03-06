%% Processor-in-the-Loop (PIL) simulation with TI Stellaris LaunchPad
%% General information
% Read more about PIL in documentation:
% <matlab:web([docroot,'/ecoder/processor-in-the-loop.html'])
% Processor-in-the-Loop (PIL) Simulation>
%% PIL simple model
% This demo shows a simple model with three inputs and three outputs,
% running in PIL Mode. All inputs have different data types and sizes.
% Start simulation and play around with source blocks. Open the model:
% <matlab:stellaris_test_pil stellaris_test_pil>
%% PIL execution profiling
% This demo shows a simple multirate model. The referenced model is running
% three rates: 10 ms, 50 ms and 100 ms. After you stop simulation, you will
% see Execution Profile report and Execution Profile in Simulink Data
% Inspector. Observe that the execution time changes depending on how many
% rates need to be run in the specific time step. Every 100 ms all three
% rates have to run, every 50 ms two rates have to run (50 ms and 10 ms),
% and every 10 ms there is only one rate to run. Open the model:
% <matlab:stellaris_test_pil_profile stellaris_test_pil_profile>
%% PIL FFT example
% This demo shows an FFT running in PIL simulation. You might want to
% enable profiling and explore how long it takes to run FFT on the actual
% processor. You can find out that data transmission over serial channel is
% a bottleneck. Nevertheless, it's just a fun demo to play with. Open the
% model: <matlab:stellaris_fft_system stellaris_fft_system>