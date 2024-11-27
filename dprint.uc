// bytecode : ucode -o dprint dprint.uc                                          
import { display } from 'cinuc';
                                             
if (length(ARGV)<2) {                      
    print("usage dprint <delay> <text>");
    return;
}                              
                                   
display(ARGV[0]).dprint(ARGV[1]);
