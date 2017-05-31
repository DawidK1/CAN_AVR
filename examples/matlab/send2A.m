%this function is used to send 2.0A standard CAN frame to CAN-AVR
function send2A(s,ID,DLC,DATA)


    CMD=1; %command to send not-extended frame

    ID = uint16(ID);
    
    IDtag0=uint8(mod(ID,256));
    IDtag1=uint8(mod(shiftbit(ID,-8),256) );


    buff=uint8([CMD, IDtag0, IDtag1, DLC, DATA]);

    fwrite(s,buff);


end
