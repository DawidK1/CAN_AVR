CMD=1;

field1	 = 'LiftAxle2Alert_cmd' ;	value1	 = 7 ;
field2	 = 'AdBlueLevelLowAlert_cmd' ;	value2	 = 7 ;
field3	 = 'LiftAxle1Alert_cmd' ;	value3	 = 7 ;
field4	 = 'DirIndicatorRightAlert_cmd' ;	value4	 = 7 ;
field5	 = 'MainBeamAlert_cmd' ;	value5	 = 7 ;
field6	 = 'DippedBeamAlert_cmd' ;	value6	 = 7 ;
field7	 = 'DirIndicatorRtTrailerAlert_cmd' ;	value7	 = 7 ;
field8	 = 'ParkBrakeAlert_cmd' ;	value8	 = 7 ;
field9	 = 'ExtraSpotLampsAlert_cmd' ;	value9	 = 7 ;
field10	 = 'DirIndicatorLeftAlert_cmd' ;	value10	 = 7 ;
field11	 = 'FogLightRearAlert_cmd' ;	value11	 = 7 ;
field12	 = 'CheckAlert_cmd' ;	value12	 = 2 ;
field13	 = 'FuelLevelLowAlert_cmd' ;	value13	 = 7 ;
field14	 = 'EngineMalFunctionAlert_cmd' ;	value14	 = 7 ;
field15	 = 'DirIndicatorLtTrailerAlert_cmd' ;	value15	 = 7 ;
field16	 = 'FogLightFrontAlert_cmd' ;	value16	 = 7 ;
field17	 = 'PosLightAlert_cmd' ;	value17	 = 7 ;
field18	 = 'StopAlert_cmd' ;	value18	 = 7 ;
field19	 = 'VehicleMode' ;	value19	 = 4 ;
field20	 = 'VehicleMode_UB' ;	value20	 = 1 ;
ID='ID'; id_v= 285151215;
DLC='DLC'; dlc_v= 8;


msg=struct(ID,id_v,DLC,dlc_v,	field1	,value1	,field2	,value2	,field3	,value3	,field4	,value4	,field5	,value5	,field6	,value6	,field7	,value7	,field8	,value8	,field9	,value9	,field10	,value10	,field11	,value11	,field12	,value12	,field13	,value13	,field14	,value14	,field15	,value15	,field16	,value16	,field17	,value17	,field18	,value18	,field19	,value19	,field20	,value20	)
   
    
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
IDtag0=uint8(mod(ID,256));
IDtag1=uint8( mod(bitshift(ID,-8, 'uint32'), 256) );
IDtag2=uint8( mod(bitshift(ID,-16, 'uint32'), 256) );
IDtag3=uint8( mod(bitshift(ID,-24, 'uint32'), 256) );
DATAtag0=uint8(mod(data,256));
DATAtag1=uint8(mod(bitshift(data,-8),256));
DATAtag2=uint8(mod(bitshift(data,-16),256));
DATAtag3=uint8(mod(DATA,256));
DATAtag4=uint8(mod(bitshift(DATA,-8),256));
DATAtag5=uint8(mod(bitshift(DATA,-16),256));
DATAtag6=uint8(mod(bitshift(DATA,-24),256));
DATAtag7=uint8(mod(bitshift(DATA,-32),256));
dec2bin(mod(DATA,(2^8)));

buff=uint8([CMD, IDtag0, IDtag1,IDtag2, IDtag3, msg.DLC, DATAtag0 DATAtag1 DATAtag2 DATAtag3 DATAtag4 DATAtag5 DATAtag6 DATAtag7]);
                
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    