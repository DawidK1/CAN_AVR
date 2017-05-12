function msg = msg_gen()
            field1	 = 'LiftAxle2Alert_cmd' ;	value1	 = 0 ;
            field2	 = 'AdBlueLevelLowAlert_cmd' ;	value2	 = 0 ;
            field3	 = 'LiftAxle1Alert_cmd' ;	value3	 = 0 ;
            field4	 = 'DirIndicatorRightAlert_cmd' ;	value4	 = 0 ;
            field5	 = 'MainBeamAlert_cmd' ;	value5	 = 0 ;
            field6	 = 'DippedBeamAlert_cmd' ;	value6	 = 0 ;
            field7	 = 'DirIndicatorRtTrailerAlert_cmd' ;	value7	 = 0 ;
            field8	 = 'ParkBrakeAlert_cmd' ;	value8	 = 0 ;
            field9	 = 'ExtraSpotLampsAlert_cmd' ;	value9	 = 0 ;
            field10	 = 'DirIndicatorLeftAlert_cmd' ;	value10	 = 0 ;
            field11	 = 'FogLightRearAlert_cmd' ;	value11	 = 0 ;
            field12	 = 'CheckAlert_cmd' ;	value12	 = 0 ;
            field13	 = 'FuelLevelLowAlert_cmd' ;	value13	 = 0 ;
            field14	 = 'EngineMalFunctionAlert_cmd' ;	value14	 = 0 ;
            field15	 = 'DirIndicatorLtTrailerAlert_cmd' ;	value15	 = 0 ;
            field16	 = 'FogLightFrontAlert_cmd' ;	value16	 = 0 ;
            field17	 = 'PosLightAlert_cmd' ;	value17	 = 0 ;
            field18	 = 'StopAlert_cmd' ;	value18	 = 0 ;
            field19	 = 'VehicleMode' ;	value19	 = 4 ;
            field20	 = 'VehicleMode_UB' ;	value20	 = 1 ;
            ID='ID'; id_v= 285151215;
            DLC='DLC'; dlc_v= 8;


            msg=struct(ID,id_v,DLC,dlc_v,...
            field1	,value1	,field2	,value2	,field3	,value3	,field4	,value4	,field5	,value5	,field6	,value6	,field7,...
            value7	,field8	,value8	,field9	,value9	,field10	,value10	,field11	,value11	,field12	,value12...
            ,field13	,value13	,field14	,value14	,field15	,value15	,field16	,value16...
            ,field17	,value17	,field18	,value18	,field19	,value19	,field20	,value20	)
    
        end