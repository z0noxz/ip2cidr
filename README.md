ip2cidr
======
ip2cidr is a small and simple program for converting ip address (mask) into a
CIDR, or returing an already valid one.

Installation
------------
Edit config.mk to match your local setup (ip2cidr is installed into the
/usr/local namespace by default), then simply enter the following command to
install (if necessary as root):

    make clean install

Usage example of ip2cidr
------------------------
Allow user to enter a subnet mask as either a CIDR or as an ip address:

    read -p "enter subnet mask: " output; output=$(ip2cidr "$output")

