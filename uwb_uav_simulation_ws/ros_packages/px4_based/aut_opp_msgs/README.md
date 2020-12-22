# aut_opp_msgs
This package defines the messages to be used in by the action servers and client in the `aut_opp` package. The folder **action** holds to action files, MoveDrone.action and Start.action.

## MoveDrone.action
Used to call the `move_drone` server. 

**goal**: is a string with the artag that needs to be found.  

**result**: is a string with the either POSREACHED or POSNOTREACHED as result.

**feedback**: is a string with the current state of the server. 

## Start.action
Used to call the `start` server.

**goal**: string with the mode that needs to be set for the drone. 

**result**: string with the result (no specific use yet).

**feedback**: string with the curent state of the server. 
