% See "Test an rtiostream Driver":
% web([docroot '/ecoder/ug/creating-a-connectivity-configuration-for-a-target.html'])
% Run the "rtiostreamtest_stellaris" project in CCS.
% Then run this command:
rtiostreamtest('serial',getpref('stellaris','COMPort'),115200);