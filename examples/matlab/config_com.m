%use this function once to configure your uart-usb serial device.
%change COM parametr, check your uart-usb COM number in device manager

%do not change rest of parameters

s = serial('COM11');

set(s,'BaudRate',500000);
s.StopBits=1;
s.Parity='none';
  fopen(s);
s
