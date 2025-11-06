#!/bin/bash
opt=1
fileName=""
while true
do
echo -e "\n1. Create Address Book"
echo "2. View Records"
echo "3. Insert new Record"
echo "4. Delete a Record"
echo "5. Modify a Record"
echo "6. Exit"
echo
read -p "Enter your choice: " opt
case $opt in
1)
read -p "Enter filename: " filename
printf
"NAME\t\tNUMBER\t\t\tADDRESS\n===========================================
===\n" > "$fileName"
while true
do read -p "Enter Name: " name
read -p "Enter Phone Number of $name: " number
read -p "Enter Address of $name: " address
printf "$name\t$number\t\t$address\n" >> "$fileName"
read -p "Enter 0 to Stop, 1 to Continue: " cont
[ "$cont" -eq 0 ] && break
done
;;
2)
if [ ! -f "$fileName" ]; then
echo "No address book found!"
else
cat "$fileName"
fi
;;
3)
read -p "Enter Name: " name
read -p "Enter Phone Number of $name: " number
read -p "Enter Address of $name: " address
printf "$name\t$number\t\t$address\n" >> "$fileName"
;;
4)
read -p "Enter Name/Phone Number to Delete: " pattern
grep -v "$pattern" "$fileName" > temp && mv temp "$fileName"
;;
5)
read -p "Enter Name/Phone Number to Modify: " pattern
grep -v "$pattern" "$fileName" > temp && mv temp "$fileName"
read -p "Enter New Name: " name
read -p "Enter New Phone Number of $name: " number
read -p "Enter New Address of $name: " address
printf "$name\t$number\t\t$address\n" >> "$fileName"
;; 
6)
echo "Exiting program..."
exit 0
;; *) echo "Invalid option!" ;; 
esac 
done