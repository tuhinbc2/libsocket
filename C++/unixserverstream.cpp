# include <string>
/*
The committers of the libsocket project, all rights reserved
(c) 2012, dermesser <lbo@spheniscida.de>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
	disclaimer.
	2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
	disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

/*
 * DESCRIPTION FOR UNIXSERVERSTREAM.CPP
 *	Provides a UNIX domain STREAM server.
 *	The path given at the constructors is the bind
 *	path. accept() accepts a new connection and returns
 *	(like inet_stream_server) a pointer to a dynamically allocated
 *	instance of unix_stream_client which may be used to
 *	communicate with the connected client.
 */

# include "../headers/libunixsocket.h"
# include "../headers/exception.hpp"
# include "../headers/unixserverstream.hpp"

namespace libsocket
{
	using std::string;

	unix_stream_server::unix_stream_server(void)
	{
	}

	unix_stream_server::unix_stream_server(const char* path, int flags)
	{
		setup(path,flags);
	}

	unix_stream_server::unix_stream_server(const string& path, int flags)
	{
		setup(path,flags);
	}

	void unix_stream_server::setup(const char* path, int flags)
	{
		if ( sfd != -1 )
			throw socket_exception(__FILE__,__LINE__,"unix_stream_server::setup: Socket already set up!\n");
		if ( path == NULL )
			throw socket_exception(__FILE__,__LINE__,"unix_stream_server::setup: Path is NULL!\n");

		sfd = create_unix_server_socket(path,STREAM,flags);

		_path.assign(path);

		if ( sfd < 0 )
			throw socket_exception(__FILE__,__LINE__,"unix_stream_server::setup: Error at creating UNIX stream server socket!\n");
	}

	void unix_stream_server::setup(const string& path, int flags)
	{
		setup(path.c_str(),flags);
	}

	unix_stream_client* unix_stream_server::accept(int flags)
	{
		if ( sfd == -1 )
			throw socket_exception(__FILE__,__LINE__,"unix_stream_server::accept: Socket not set up yet!\n");

		unix_stream_client* client = new unix_stream_client;

		int cfd = accept_unix_stream_socket(sfd,flags);

		if ( cfd < 0 )
			throw socket_exception(__FILE__,__LINE__,"unix_stream_server::accept: Error at accepting new connection!\n");

		client->sfd = cfd;

		return client;
	}

}
