CC= gcc

client.run:client.c server.run
	$(CC) -o client.run client.c
server.run:server.c
	$(CC) -o server.run server.c
