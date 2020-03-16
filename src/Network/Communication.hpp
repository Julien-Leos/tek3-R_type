/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Communication
*/

#ifndef COMMUNICATION_HPP_
#define COMMUNICATION_HPP_

#include <cstddef>
#include <sstream>

#define EMPTY_PROTOCOL(struct) memset(&(struct), 0, sizeof(protocol_t));struct.object.pos={-1, -1};struct.object.velocity={-1, -1}
#define MESSAGE_SIZE 512

/**
 * @brief A vector of two int used to describe a 2D position or velocity
 *
 */
typedef struct pos_s {
    float x;
    float y;
} pos_t;

/**
 * @brief Everything needed to create an object is in this structure
 *
 */
typedef struct object_s {
    /**
     * @brief Id of the type of the object (ex: ennemy, bullets, spaceship, ...)
     *
     */
    unsigned char type;

    /**
     * @brief If the object collide with other object or not
     *
     */
    bool isCollide;

    /**
     * @brief Position of the object
     *
     */
    pos_t pos;

    /**
     * @brief Velocity of the object
     *
     */
    pos_t velocity;
} object_t;

typedef struct protocol_t {
    /**
     * @brief Code to recognize the wanted action
     *
     */
    unsigned char opcode;
    /**
     * @brief Id of the client which send or receive the packet
     *
     */
    unsigned int clientId;
    /**
     * @brief Optional data which might be necessary for some protocol operation
     *
     */
    std::size_t data;
    /**
     * @brief Optional object which might be necessary for some protocol
     * operation
     *
     */
    object_t object;
} protocol_t;

typedef struct communication_s {
    protocol_t protocol;
    char string[MESSAGE_SIZE];
} communication_t;

#endif /* !COMMUNICATION_HPP_ */

/*
Vie : Object (Object properties) Data (Vies)
Score : Object (Object properties) Data (Vies)
//// OTHER /////
 1 - Init | Server -> Client | ClientId (Id du client)

//// GAME (UDP) ////
100 - Object (1: Create, 2: Update, 3: Delete)
    101 - Create | Server -> Client | Data (Object ID) Object (Object properties)
    102 - Update | Server -> Client | Data (Object ID) Object (Object properties)
    103 - Delete | Server -> Client | Data (Object ID)
110 - Input
    110 - Client -> Server | ClientID (ObjectId) ; Data (InputId)

//// LOBBY (TCP) /////
010 - Connexion (1: Connect, 2: Disconnect)
    011 - Connect | Client -> Server | Text (Pseudo)
    011 - Connect | Server -> Client | Data (Client ID) Text (pseudo)
    012 - Disconnect | Client -> Server
    012 - Disconnect | Server -> Client
020 - Room (1: Create, 2: Join, 3: Leave, 4: Delete, 5: Get)
    021 - Create | Client -> Server | Text (Room name)
    021 - Create | Server -> Client | Data (Room ID) Text (Room name)
    022 - Join | Client -> Server | Data (Room ID)
    022 - Join | Server -> Client |
    023 - Leave | Client -> Server |
    023 - Leave | Server -> Client | Data (Client ID)
    024 - Delete | Server -> Client | Data (Room ID)
    025 - Get | Server -> Client | Data (Room ID) Text (Room name)
    026 - Player Ready | Client -> Server |
    026 - Player Ready | Server -> Client | Data (Client ID)
    027 - Get Player | Client -> Server | Data (Room ID)
    027 - Get Player | Server -> Client | Data (Client ID) Text (Pseudo)
030 - Game (1: Start, 2: End)
    031 - Start | Server -> Client | Data (Creation time ms)
    032 - End | Server -> Client |
040 - Message
    040 - Client -> Server | Data (Message size) Text (Message)
    040 - Server -> Client | Data (Message size) Text (Pseudo + Message)
*/