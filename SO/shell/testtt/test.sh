files=`ls -l | grep -E '^[-rwx]{8}w' | awk '{print $9}'`
 for file in $files; do 
   chmod o-w $file 
 done
