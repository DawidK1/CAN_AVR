function msg = msg_gen3()
%generate HMIIOM_Displ_11P
            field2	 = 'SIDOnOff' ;	value2	 = 0 ;
            field1	 = 'SelectLanguage' ;	value1	 = 0 ;
            field3	 = 'ClusterDispIllumLvl_cmd' ;	value3	 = 0 ;
            field4	 = 'DIDIlluminationLevel_cmd' ;	value4	 = 0 ;
            field5	 = 'SIDIlluminationLevel_cmd' ;	value5	 = 0 ;
            field6	 = 'GaugeIlluminationLevel_cmd' ;	value6	 = 0 ;
            field7	 = 'ContrastLevel_cmd' ;	value7	 = 0 ;
            field9	 = 'LEDIntensity' ;	value9	 = 0 ;
            field8	 = 'Backlight_cmd' ;	value8	 = 0 ;
            field10	 = 'TeltaleIntensity' ;	value10	 = 0 ;
            ID='ID'; id_v= 285192159;
            DLC='DLC'; dlc_v= 8;


            msg=struct(ID,id_v,DLC,dlc_v,...
            field1	,value1	,field2	,value2	,field3	,value3	,field4	,value4	,field5	,value5	,field6	,value6	,field7,...
            value7	,field8	,value8	,field9	,value9	,field10	,value10)
    
        end