/* Serve
 * The backbone of a basic server
*/

#include "serve.h"

int main(int argc, char **argv)
{
	/* Set up the server. */
	printf("Starting server...");
	GSocketAddress *address = g_inet_socket_address_new_from_string("0.0.0.0", 15080);
	GSocket *server = g_socket_new(G_SOCKET_FAMILY_IPV4, G_SOCKET_TYPE_STREAM, G_SOCKET_PROTOCOL_TCP, NULL);
	g_socket_bind(server, address, TRUE, NULL);
	g_socket_listen(server, NULL);
	printf("Done\n");
	/* Listen for a connection */
	printf("Waiting for a connection...\n");
	GSocket *client = g_socket_accept(server, NULL, NULL);
	/* Accept connection, display details. */
	GInetSocketAddress *clientSocketAddress = g_socket_get_remote_address(client, NULL);
	GInetAddress *clientAddress = g_inet_socket_address_get_address(clientSocketAddress);
	g_object_ref(clientAddress);
	gchar *clientAddressString = g_inet_address_to_string(clientAddress);
	guint16 clientPort = g_inet_socket_address_get_port(clientSocketAddress);
	printf("Client connected from %s:%d\n", clientAddressString, clientPort);
	g_object_unref(clientAddress);
	g_free(clientAddressString);
	/* Send a small amount of test data through, then close. */
	g_socket_send(client, "Hello world!", 13, NULL, NULL);
	/* Shut down the server. */
	printf("Shutting down server...");
	g_socket_close(server, NULL);
	printf("Done\n");
	return 0;
}
