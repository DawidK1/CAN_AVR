function send2B(s,ID,DLC,DATA)%this function is used to send 2.0B extended CAN frame to CAN-AVR


    CMD = 2;
    
    ID = uint32(ID);
    IDtag0=uint8(mod(ID,256));
    IDtag1=uint8( mod(bitshift(ID,-8, 'uint32'), 256) );
    IDtag2=uint8( mod(bitshift(ID,-16, 'uint32'), 256) );
    IDtag3=uint8( mod(bitshift(ID,-24, 'uint32'), 256) );
    buff=uint8([CMD, IDtag0, IDtag1,IDtag2, IDtag3, DLC, DATA]);
    fwrite(s,buff);
end
