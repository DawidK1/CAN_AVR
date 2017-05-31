
%in this example fixed data are sent to CAN-AVR cyclic by usb-avr device,
%and CAN-AVR put them to CAN bus. In specific application you can change data 
%and ID to communicate with other devices connected to CAN bus.


%if you dont have variable s initialized config your com port, using config_com.m

mydata = [133 133 133 33 55 55 64 ];

while 1
    pause(0.01); %wait 10 ms, which give 100Hz message frequency
    
    send2B(s,111,7, mydata);%send a message via s stream, in extended format,
                            %ID is 111, next 7 data bytes I.E. mydata
    
end
