all:
	gcc myChat.c -o Chat
	mkfifo Chat_1
	mkfifo Chat_2
	sudo gnome-terminal -x sh -c "sudo ./Chat Chat_1 Chat_2"
	sudo ./Chat Chat_2 Chat_1
	rm Chat_1
	rm Chat_2
