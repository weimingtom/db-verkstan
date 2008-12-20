int dataSize = 57;
unsigned char data[57] = { 
                           // Header
                           0x04, // Number of operators
                          
                           // Operators
                           0x23, // CameraOperator
                           0x21, // MaterialOperator
                           0x10, // IcosahedronOperator
                           0x01, // PixelsOperator

                           // Properties
                           0x00, 0x00, 0x34, 0x42, // Angle
                           0x00, 0x40, // Ratio width
                           0x00, 0x30, // Ration height
                           0x80, 0x80, 0x80, // Clear color
                           0x00, 0x00, 0x00, 0x00, // Translation x
                           0x00, 0x00, 0x00, 0x00, // Translation y
                           0x00, 0x00, 0xa0, 0xc0, // Translation z
                           0x00, 0x00, 0x00, 0x00, // Look at x
                           0x00, 0x00, 0x00, 0x00, // Look at y
                           0x00, 0x00, 0x00, 0x00, // Look at z
                           0x00, 0x00, 0x00, 0x00, // Rotation
                           0xff, 0xff, 0xff, // Color 1
                           0x00, 0x00, 0xff, // Color 2
                           0x01, 0xff, // Count
                           0x00, 0x03, // Seed

                           // Connections
                           0x02, // Two connections
                           0x01, // InputId - OperatorId
                           0x01, // InputId - OperatorId
                         };
