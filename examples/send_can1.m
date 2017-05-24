function [  ] = send_can1(s,msg)
%send HMIIOM_Displ_01P
    CMD=2;
    CMD2=170;
    DATA=uint64(uint8(msg.LiftAxle2Alert_cmd));
    DATA=uint64(bitor(DATA,bitshift(msg.AdBlueLevelLowAlert_cmd,	3	, 'uint64')));
    DATA=uint64(bitor(DATA,bitshift(msg.LiftAxle1Alert_cmd,	6	, 'uint64')));
    DATA=uint64(bitor(DATA,bitshift(msg.DirIndicatorRightAlert_cmd,	9	, 'uint64')));
    DATA=uint64(bitor(DATA,bitshift(msg.MainBeamAlert_cmd,	12	, 'uint64')));
    DATA=uint64(bitor(DATA,bitshift(msg.DippedBeamAlert_cmd,	15	, 'uint64')));
    DATA=uint64(bitor(DATA,bitshift(msg.DirIndicatorRtTrailerAlert_cmd,	18	, 'uint64')));
    DATA=uint64(bitor(DATA,bitshift(msg.ParkBrakeAlert_cmd,	21	, 'uint64')));
    data=DATA;

    DATA=uint64((msg.ExtraSpotLampsAlert_cmd));
    DATA=uint64(bitor(DATA,bitshift(msg.DirIndicatorLeftAlert_cmd,	3	, 'uint64')));
    DATA=uint64(bitor(DATA,bitshift(msg.FogLightRearAlert_cmd,	6	, 'uint64')));
    DATA=uint64(bitor(DATA,bitshift(msg.CheckAlert_cmd,	9	, 'uint64')));

    DATA=uint64(bitor(DATA,bitshift(msg.FuelLevelLowAlert_cmd,	12	, 'uint64')));
    DATA=uint64(bitor(DATA,bitshift(msg.EngineMalFunctionAlert_cmd,	15	, 'uint64')));
    DATA=uint64(bitor(DATA,bitshift(msg.DirIndicatorLtTrailerAlert_cmd,	18	, 'uint64')));
    DATA=uint64(bitor(DATA,bitshift(msg.FogLightFrontAlert_cmd,	21	, 'uint64')));
    DATA=uint64(bitor(DATA,bitshift(msg.PosLightAlert_cmd,	24	, 'uint64')));
    DATA=uint64(bitor(DATA,bitshift(msg.StopAlert_cmd,	27	, 'uint64')));
    DATA=uint64(bitor(DATA,bitshift(msg.VehicleMode,	30	, 'uint64')));
    DATA=uint64(bitor(DATA,bitshift(msg.VehicleMode_UB,	34	, 'uint64')));

    ID = uint32(msg.ID);
    IDtag3=uint8(mod(ID,256));
    IDtag2=uint8( mod(bitshift(ID,-8, 'uint32'), 256) );
    IDtag1=uint8( mod(bitshift(ID,-16, 'uint32'), 256) );
    IDtag0=uint8( mod(bitshift(ID,-24, 'uint32'), 256) );
    DATAtag0=uint8(mod(data,256));
    DATAtag1=uint8(mod(bitshift(data,-8),256));
    DATAtag2=uint8(mod(bitshift(data,-16),256));
    DATAtag3=uint8(mod(DATA,256));
    DATAtag4=uint8(mod(bitshift(DATA,-8),256));
    DATAtag5=uint8(mod(bitshift(DATA,-16),256));
    DATAtag6=uint8(mod(bitshift(DATA,-24),256));
    DATAtag7=uint8(mod(bitshift(DATA,-32),256));
    dec2bin(mod(DATA,(2^8)));
    buff=uint8([CMD, IDtag0, IDtag1,IDtag2, IDtag3, msg.DLC, DATAtag0, DATAtag1, DATAtag2, DATAtag3, DATAtag4, DATAtag5, DATAtag6, DATAtag7,CMD2]);
      
        fwrite(s,buff);


end

