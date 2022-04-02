
/*! @class FlexiCommand
 *  @brief I/O command
 *  @author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  @todo Support more params
 */

#ifndef FLEXICOMMAND_H
#define FLEXICOMMAND_H

typedef struct flexi_command
{
	int			command;
	int			param;

	// constructor
	flexi_command(int _command, int _param) : command(_command), param(_param) {}

} FlexiCommand;

#endif
