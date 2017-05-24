

while 1
    msg= fread(s);
    first_list=find(msg == 4);

    for iter = 1:length(first_list)
        first = first_list(iter);
        
        
        if  (first+5 < length(msg)) &&...   
            (msg(first+5) < 9 ) &&... 
            (first +6 + msg(first+5) + 1 < length(msg))&&...
            (msg(first + 5 + msg(first+5) + 1 ) == 170)
           
            parse =msg(first:(6 + first + msg(first+5)));
            ID = bitshift(parse(5),21)+ bitshift(parse(4),13) + bitshift(parse(3),5) + parse(2);
            dec2hex(ID);
            DLC = parse(6);
            output = dec2hex(ID);
    
                output = strcat('ID=',output, ' DLC = ', num2str(DLC), ' DATA = ');
                for i =1:DLC
                     output = strcat(output, num2str(parse(6 +i)), '. '); % glue together frame
                end
                disp(output) % show in command window
                
        end      
    end

end
