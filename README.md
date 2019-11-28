# ircbot in c++

## Motivation

 - Want to brush up on C++
 - Converting an [existing project](https://github.com/cbosoft/ircbot) is a good
   way to improve literacy in a language

## Spec

 - Bot should respond to user commands (messages starting with a "!")
   - This could be to inform of meta-data about the log or ircserver
   - to get info about running process on a sim server
   - to perform a quick internet search
   - to record whether users are "AFK" or not, and then send to them missed
     messages when they return
 - Bot should also log the messages in the chat for posterity
