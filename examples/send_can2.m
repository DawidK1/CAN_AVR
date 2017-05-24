function [  ] = send_can2(s,msg)
%send HMIIOM_Displ_05P
    CMD=2;
    CMD2=170;
    DATA=uint64(uint16(msg.EngineSpeed));
    DATA=uint64(bitor(DATA,bitshift(msg.VehicleSpeed,	16	, 'uint64')));
    DATA=uint64(bitor(DATA,bitshift(msg.Transm,	32	, 'uint64')));
    DATA=uint64(bitor(DATA,bitshift(msg.Speedometer,	48	, 'uint64')));

    ID = uint32(msg.ID);
    IDtag3=uint8(mod(ID,256));
    IDtag2=uint8( mod(bitshift(ID,-8, 'uint32'), 256) );
    IDtag1=uint8( mod(bitshift(ID,-16, 'uint32'), 256) );
    IDtag0=uint8( mod(bitshift(ID,-24, 'uint32'), 256) );
    DATAtag0=uint8(mod(DATA,256));
    DATAtag1=uint8(mod(bitshift(DATA,-8, 'uint64'),256));
    DATAtag2=uint8(mod(bitshift(DATA,-16, 'uint64'),256));
    DATAtag3=uint8(mod(bitshift(DATA,-24, 'uint64'),256));
    DATAtag4=uint8(mod(bitshift(DATA,-32, 'uint64'),256));
    DATAtag5=uint8(mod(bitshift(DATA,-40, 'uint64'),256));
    DATAtag6=uint8(mod(bitshift(DATA,-48, 'uint64'),256));
    DATAtag7=uint8(mod(bitshift(DATA,-56, 'uint64'),256));
    dec2bin(mod(DATA,(2^8)));
    buff=uint8([CMD, IDtag0, IDtag1,IDtag2, IDtag3, msg.DLC, DATAtag0, DATAtag1, DATAtag2, DATAtag3, DATAtag4, DATAtag5, DATAtag6, DATAtag7,CMD2]);
      
        fwrite(s,buff);


end

