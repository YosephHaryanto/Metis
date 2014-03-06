/*
 * Copyright © 2012 Nokia Corporation. All rights reserved.
 * Nokia and Nokia Connecting People are registered trademarks of Nokia Corporation. 
 * Other product and company names mentioned herein may be trademarks
 * or trade names of their respective owners. 
 * See LICENSE.TXT for license information.
 */
using ProtoBuf;

namespace NFCTalk
{
    /// <summary>
    /// Representation for a single chat message.
    /// </summary>
    [ProtoContract]
    public class Message
    {
        public enum DirectionValue
        {
            In = 0,
            Out = 1
        }

        /// <summary>
        /// Direction of message, in to this device, or out to the other device.
        /// </summary>
        [ProtoMember(1)]
        public DirectionValue Direction { get; set; }

        /// <summary>
        /// Sender's name.
        /// </summary>
        [ProtoMember(2)]
        public string Name { get; set; }

        /// <summary>
        /// Message.
        /// </summary>
        [ProtoMember(3)]
        public string Text { get; set; }

        /// <summary>
        /// Is this message archived.
        /// </summary>
        [ProtoMember(4)]
        public bool Archived { get; set; }

        [ProtoMember(5)]
        public string ImageName { get; set; }

        [ProtoMember(6)]
        public byte[] ImageBytes { get; set; }

            
    }
}
