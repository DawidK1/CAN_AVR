

%in this example bytes from UART are parsed into CAN frames and displayed
%in command windows. In specific application you should use ID and data and
%react according to received messages.


%if you dont have variable s initialized config your com port, using config_com.m


while 1

    msg= fread(s); %read data from stream
    first_list=find(msg == 4);% find all possible frame begins 

    for iter = 1:length(first_list)
        first = first_list(iter);
        
        
        if  (first+5 < length(msg)) &&...   %this if is checking that found 4 is real frame begin
            (msg(first+5) < 9 ) &&... %is DLC in range (max 8)
            (first +6 + msg(first+5) + 1 < length(msg))&&...
            (msg(first + 5 + msg(first+5) + 1 ) == 170) %is end of frame found?
           
            parse =msg(first:(6 + first + msg(first+5))); %save frame to new wariable
       
            %bitshift operations is used to restore original ID from four
            %bytes i.e. bitshift(byte,4) is the same as byte * 2^4
            ID = bitshift(parse(5),21)+ bitshift(parse(4),13) + bitshift(parse(3),5) + parse(2);
            %if you want to show frame in hex use: dec2hex(ID)
            
            DLC = parse(6);
            output = dec2hex(ID);
            %data bytes is stored in  7 ... 6+DLC
                output = strcat('ID=',output, ' DLC = ', num2str(DLC), ' DATA = ');
                for i =1:DLC
                     output = strcat(output, num2str(parse(6 +i)), '. '); % glue together frame
                end
                disp(output) % show in command window
                
        end      
    end

end
