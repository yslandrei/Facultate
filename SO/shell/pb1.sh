#!/bin/bash
users=`cat who.fake | awk '{print $1}'`
for user in $users; do
  app=`cat ps.fake | grep "^$user " | wc -l`
  echo $user $app
done
