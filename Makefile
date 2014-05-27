CC= gcc

client.run:client.c server.run select_server.run select_client.run
	$(CC) -o client.run client.c
server.run:server.c
	$(CC) -o server.run server.c
select_server.run: select_server.c
	$(CC) -o select_server.run select_server.c
select_client.run: select_client.c
	$(CC) -o select_client.run select_client.c
