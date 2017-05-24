function msg = msg_gen2()
%generate HMIIOM_Displ_05P
            field1	 = 'EngineSpeed' ;	value1	 = 0 ;
            field2	 = 'VehicleSpeed' ;	value2	 = 0 ;
            field3	 = 'Transm' ;	value3	 = 0 ;
            field4	 = 'Speedometer' ;	value4	 = 0 ;
            
            ID='ID'; id_v=  285183855;
           
            DLC='DLC'; dlc_v= 8;

            msg=struct(ID,id_v,DLC,dlc_v, field1, value1, field2, value2, field3, value3, field4,value4)
    
        end