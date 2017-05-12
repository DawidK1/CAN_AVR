s = serial('COM11');
set(s,'BaudRate',500000);
s.StopBits=1;
s.Parity='none';
  fopen(s);
s
