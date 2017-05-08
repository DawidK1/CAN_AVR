
%open com port, speed 115200, one stop bit, no parity bits
s = serial('COM11');
set(s,'BaudRate',115200);
s.StopBits=1;
s.Parity='none';
  fopen(s);
s

mydata = [133 133 133 33 55 55 64 ];

while 1
    pause(0.001);
    send2B(s,111,7, mydata);%send a message in extended format, ID is 111, next 7 data bytes I.E. mydata
    
end
