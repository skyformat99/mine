#ifndef AES_TEST_H
#define AES_TEST_H

#include "test.h"

#ifdef MINE_SINGLE_HEADER_TEST
#   include "package/mine.h"
#else
#   include "src/aes.h"
#endif

namespace mine {


// from http://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38a.pdf

static const AES::ByteArray kNistIV = {{
                                           0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                           0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
                                       }};

static const AES::Key kNistKey128 = {{
                                         0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                                         0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
                                     }};

static const AES::Key kNistKey192 = {{
                                         0x8e, 0x73, 0xb0, 0xf7, 0xda, 0x0e, 0x64, 0x52,
                                         0xc8, 0x10, 0xf3, 0x2b, 0x80, 0x90, 0x79, 0xe5,
                                         0x62, 0xf8, 0xea, 0xd2, 0x52, 0x2c, 0x6b, 0x7b
                                     }};

static const AES::Key kNistKey256 = {{
                                         0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe,
                                         0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
                                         0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7,
                                         0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4
                                     }};

TEST(AESTest, KeyExpansion)
{
    // This key expansion is original key from FIPS.197 example
    static TestData<std::string, AES::Key, AES::KeySchedule> KeyExpansionTestData = {
        TestCase("128-bit key expansion", AES::Key{{
                                                       0x2b, 0x7e, 0x15, 0x16,
                                                       0x28, 0xae, 0xd2, 0xa6,
                                                       0xab, 0xf7, 0x15, 0x88,
                                                       0x09, 0xcf, 0x4f, 0x3c
                                                   }}, AES::KeySchedule{{
                                                                          {0, {{ 0x2B, 0x7E, 0x15, 0x16 }}},
                                                                          {1, {{ 0x28, 0xAE, 0xD2, 0xA6 }}},
                                                                          {2, {{ 0xAB, 0xF7, 0x15, 0x88 }}},
                                                                          {3, {{ 0x9, 0xCF, 0x4F, 0x3C }}},
                                                                          {4, {{ 0xA0, 0xFA, 0xFE, 0x17 }}},
                                                                          {5, {{ 0x88, 0x54, 0x2C, 0xB1 }}},
                                                                          {6, {{ 0x23, 0xA3, 0x39, 0x39 }}},
                                                                          {7, {{ 0x2A, 0x6C, 0x76, 0x5 }}},
                                                                          {8, {{ 0xF2, 0xC2, 0x95, 0xF2 }}},
                                                                          {9, {{ 0x7A, 0x96, 0xB9, 0x43 }}},
                                                                          {10, {{ 0x59, 0x35, 0x80, 0x7A }}},
                                                                          {11, {{ 0x73, 0x59, 0xF6, 0x7F }}},
                                                                          {12, {{ 0x3D, 0x80, 0x47, 0x7D }}},
                                                                          {13, {{ 0x47, 0x16, 0xFE, 0x3E }}},
                                                                          {14, {{ 0x1E, 0x23, 0x7E, 0x44 }}},
                                                                          {15, {{ 0x6D, 0x7A, 0x88, 0x3B }}},
                                                                          {16, {{ 0xEF, 0x44, 0xA5, 0x41 }}},
                                                                          {17, {{ 0xA8, 0x52, 0x5B, 0x7F }}},
                                                                          {18, {{ 0xB6, 0x71, 0x25, 0x3B }}},
                                                                          {19, {{ 0xDB, 0xB, 0xAD, 0x00 }}},
                                                                          {20, {{ 0xD4, 0xD1, 0xC6, 0xF8 }}},
                                                                          {21, {{ 0x7C, 0x83, 0x9D, 0x87 }}},
                                                                          {22, {{ 0xCA, 0xF2, 0xB8, 0xBC }}},
                                                                          {23, {{ 0x11, 0xF9, 0x15, 0xBC }}},
                                                                          {24, {{ 0x6D, 0x88, 0xA3, 0x7A }}},
                                                                          {25, {{ 0x11, 0xB, 0x3E, 0xFD }}},
                                                                          {26, {{ 0xDB, 0xF9, 0x86, 0x41 }}},
                                                                          {27, {{ 0xCA, 0x00, 0x93, 0xFD }}},
                                                                          {28, {{ 0x4E, 0x54, 0xF7, 0xE }}},
                                                                          {29, {{ 0x5F, 0x5F, 0xC9, 0xF3 }}},
                                                                          {30, {{ 0x84, 0xA6, 0x4F, 0xB2 }}},
                                                                          {31, {{ 0x4E, 0xA6, 0xDC, 0x4F }}},
                                                                          {32, {{ 0xEA, 0xD2, 0x73, 0x21 }}},
                                                                          {33, {{ 0xB5, 0x8D, 0xBA, 0xD2 }}},
                                                                          {34, {{ 0x31, 0x2B, 0xF5, 0x60 }}},
                                                                          {35, {{ 0x7F, 0x8D, 0x29, 0x2F }}},
                                                                          {36, {{ 0xAC, 0x77, 0x66, 0xF3 }}},
                                                                          {37, {{ 0x19, 0xFA, 0xDC, 0x21 }}},
                                                                          {38, {{ 0x28, 0xD1, 0x29, 0x41 }}},
                                                                          {39, {{ 0x57, 0x5C, 0x00, 0x6E }}},
                                                                          {40, {{ 0xD0, 0x14, 0xF9, 0xA8 }}},
                                                                          {41, {{ 0xC9, 0xEE, 0x25, 0x89 }}},
                                                                          {42, {{ 0xE1, 0x3F, 0xC, 0xC8 }}},
                                                                          {43, {{ 0xB6, 0x63, 0xC, 0xA6 }}}
                                                                      }}),
        TestCase("192-bit key expansion", AES::Key{{
                                                       0x8e, 0x73, 0xb0, 0xf7,
                                                       0xda, 0x0e, 0x64, 0x52,
                                                       0xc8, 0x10, 0xf3, 0x2b,
                                                       0x80, 0x90, 0x79, 0xe5,
                                                       0x62, 0xf8, 0xea, 0xd2,
                                                       0x52, 0x2c, 0x6b, 0x7b
                                                   }}, AES::KeySchedule{{
                                                                          {0, {{ 0x8E, 0x73, 0xB0, 0xF7 }}},
                                                                          {1, {{ 0xDA, 0xE, 0x64, 0x52 }}},
                                                                          {2, {{ 0xC8, 0x10, 0xF3, 0x2B }}},
                                                                          {3, {{ 0x80, 0x90, 0x79, 0xE5 }}},
                                                                          {4, {{ 0x62, 0xF8, 0xEA, 0xD2 }}},
                                                                          {5, {{ 0x52, 0x2C, 0x6B, 0x7B }}},
                                                                          {6, {{ 0xFE, 0xC, 0x91, 0xF7 }}},
                                                                          {7, {{ 0x24, 0x2, 0xF5, 0xA5 }}},
                                                                          {8, {{ 0xEC, 0x12, 0x6, 0x8E }}},
                                                                          {9, {{ 0x6C, 0x82, 0x7F, 0x6B }}},
                                                                          {10, {{ 0xE, 0x7A, 0x95, 0xB9 }}},
                                                                          {11, {{ 0x5C, 0x56, 0xFE, 0xC2 }}},
                                                                          {12, {{ 0x4D, 0xB7, 0xB4, 0xBD }}},
                                                                          {13, {{ 0x69, 0xB5, 0x41, 0x18 }}},
                                                                          {14, {{ 0x85, 0xA7, 0x47, 0x96 }}},
                                                                          {15, {{ 0xE9, 0x25, 0x38, 0xFD }}},
                                                                          {16, {{ 0xE7, 0x5F, 0xAD, 0x44 }}},
                                                                          {17, {{ 0xBB, 0x9, 0x53, 0x86 }}},
                                                                          {18, {{ 0x48, 0x5A, 0xF0, 0x57 }}},
                                                                          {19, {{ 0x21, 0xEF, 0xB1, 0x4F }}},
                                                                          {20, {{ 0xA4, 0x48, 0xF6, 0xD9 }}},
                                                                          {21, {{ 0x4D, 0x6D, 0xCE, 0x24 }}},
                                                                          {22, {{ 0xAA, 0x32, 0x63, 0x60 }}},
                                                                          {23, {{ 0x11, 0x3B, 0x30, 0xE6 }}},
                                                                          {24, {{ 0xA2, 0x5E, 0x7E, 0xD5 }}},
                                                                          {25, {{ 0x83, 0xB1, 0xCF, 0x9A }}},
                                                                          {26, {{ 0x27, 0xF9, 0x39, 0x43 }}},
                                                                          {27, {{ 0x6A, 0x94, 0xF7, 0x67 }}},
                                                                          {28, {{ 0xC0, 0xA6, 0x94, 0x7 }}},
                                                                          {29, {{ 0xD1, 0x9D, 0xA4, 0xE1 }}},
                                                                          {30, {{ 0xEC, 0x17, 0x86, 0xEB }}},
                                                                          {31, {{ 0x6F, 0xA6, 0x49, 0x71 }}},
                                                                          {32, {{ 0x48, 0x5F, 0x70, 0x32 }}},
                                                                          {33, {{ 0x22, 0xCB, 0x87, 0x55 }}},
                                                                          {34, {{ 0xE2, 0x6D, 0x13, 0x52 }}},
                                                                          {35, {{ 0x33, 0xF0, 0xB7, 0xB3 }}},
                                                                          {36, {{ 0x40, 0xBE, 0xEB, 0x28 }}},
                                                                          {37, {{ 0x2F, 0x18, 0xA2, 0x59 }}},
                                                                          {38, {{ 0x67, 0x47, 0xD2, 0x6B }}},
                                                                          {39, {{ 0x45, 0x8C, 0x55, 0x3E }}},
                                                                          {40, {{ 0xA7, 0xE1, 0x46, 0x6C }}},
                                                                          {41, {{ 0x94, 0x11, 0xF1, 0xDF }}},
                                                                          {42, {{ 0x82, 0x1F, 0x75, 0xA }}},
                                                                          {43, {{ 0xAD, 0x7, 0xD7, 0x53 }}},
                                                                          {44, {{ 0xCA, 0x40, 0x5, 0x38 }}},
                                                                          {45, {{ 0x8F, 0xCC, 0x50, 0x6 }}},
                                                                          {46, {{ 0x28, 0x2D, 0x16, 0x6A }}},
                                                                          {47, {{ 0xBC, 0x3C, 0xE7, 0xB5 }}},
                                                                          {48, {{ 0xE9, 0x8B, 0xA0, 0x6F }}},
                                                                          {49, {{ 0x44, 0x8C, 0x77, 0x3C }}},
                                                                          {50, {{ 0x8E, 0xCC, 0x72, 0x4 }}},
                                                                          {51, {{ 0x1, 0x0, 0x22, 0x2 }}},

                                                                      }}),

        TestCase("256-bit key expansion", AES::Key{{
                                                       0x60, 0x3d, 0xeb, 0x10,
                                                       0x15, 0xca, 0x71, 0xbe,
                                                       0x2b, 0x73, 0xae, 0xf0,
                                                       0x85, 0x7d, 0x77, 0x81,
                                                       0x1f, 0x35, 0x2c, 0x07,
                                                       0x3b, 0x61, 0x08, 0xd7,
                                                       0x2d, 0x98, 0x10, 0xa3,
                                                       0x09, 0x14, 0xdf, 0xf4
                                                   }}, AES::KeySchedule{{
                                                                          {0, {{ 0x60, 0x3D, 0xEB, 0x10 }}},
                                                                          {1, {{ 0x15, 0xCA, 0x71, 0xBE }}},
                                                                          {2, {{ 0x2B, 0x73, 0xAE, 0xF0 }}},
                                                                          {3, {{ 0x85, 0x7D, 0x77, 0x81 }}},
                                                                          {4, {{ 0x1F, 0x35, 0x2C, 0x7 }}},
                                                                          {5, {{ 0x3B, 0x61, 0x8, 0xD7 }}},
                                                                          {6, {{ 0x2D, 0x98, 0x10, 0xA3 }}},
                                                                          {7, {{ 0x9, 0x14, 0xDF, 0xF4 }}},
                                                                          {8, {{ 0x9B, 0xA3, 0x54, 0x11 }}},
                                                                          {9, {{ 0x8E, 0x69, 0x25, 0xAF }}},
                                                                          {10, {{ 0xA5, 0x1A, 0x8B, 0x5F }}},
                                                                          {11, {{ 0x20, 0x67, 0xFC, 0xDE }}},
                                                                          {12, {{ 0xA8, 0xB0, 0x9C, 0x1A }}},
                                                                          {13, {{ 0x93, 0xD1, 0x94, 0xCD }}},
                                                                          {14, {{ 0xBE, 0x49, 0x84, 0x6E }}},
                                                                          {15, {{ 0xB7, 0x5D, 0x5B, 0x9A }}},
                                                                          {16, {{ 0xD5, 0x9A, 0xEC, 0xB8 }}},
                                                                          {17, {{ 0x5B, 0xF3, 0xC9, 0x17 }}},
                                                                          {18, {{ 0xFE, 0xE9, 0x42, 0x48 }}},
                                                                          {19, {{ 0xDE, 0x8E, 0xBE, 0x96 }}},
                                                                          {20, {{ 0xB5, 0xA9, 0x32, 0x8A }}},
                                                                          {21, {{ 0x26, 0x78, 0xA6, 0x47 }}},
                                                                          {22, {{ 0x98, 0x31, 0x22, 0x29 }}},
                                                                          {23, {{ 0x2F, 0x6C, 0x79, 0xB3 }}},
                                                                          {24, {{ 0x81, 0x2C, 0x81, 0xAD }}},
                                                                          {25, {{ 0xDA, 0xDF, 0x48, 0xBA }}},
                                                                          {26, {{ 0x24, 0x36, 0xA, 0xF2 }}},
                                                                          {27, {{ 0xFA, 0xB8, 0xB4, 0x64 }}},
                                                                          {28, {{ 0x98, 0xC5, 0xBF, 0xC9 }}},
                                                                          {29, {{ 0xBE, 0xBD, 0x19, 0x8E }}},
                                                                          {30, {{ 0x26, 0x8C, 0x3B, 0xA7 }}},
                                                                          {31, {{ 0x9, 0xE0, 0x42, 0x14 }}},
                                                                          {32, {{ 0x68, 0x0, 0x7B, 0xAC }}},
                                                                          {33, {{ 0xB2, 0xDF, 0x33, 0x16 }}},
                                                                          {34, {{ 0x96, 0xE9, 0x39, 0xE4 }}},
                                                                          {35, {{ 0x6C, 0x51, 0x8D, 0x80 }}},
                                                                          {36, {{ 0xC8, 0x14, 0xE2, 0x4 }}},
                                                                          {37, {{ 0x76, 0xA9, 0xFB, 0x8A }}},
                                                                          {38, {{ 0x50, 0x25, 0xC0, 0x2D }}},
                                                                          {39, {{ 0x59, 0xC5, 0x82, 0x39 }}},
                                                                          {40, {{ 0xDE, 0x13, 0x69, 0x67 }}},
                                                                          {41, {{ 0x6C, 0xCC, 0x5A, 0x71 }}},
                                                                          {42, {{ 0xFA, 0x25, 0x63, 0x95 }}},
                                                                          {43, {{ 0x96, 0x74, 0xEE, 0x15 }}},
                                                                          {44, {{ 0x58, 0x86, 0xCA, 0x5D }}},
                                                                          {45, {{ 0x2E, 0x2F, 0x31, 0xD7 }}},
                                                                          {46, {{ 0x7E, 0xA, 0xF1, 0xFA }}},
                                                                          {47, {{ 0x27, 0xCF, 0x73, 0xC3 }}},
                                                                          {48, {{ 0x74, 0x9C, 0x47, 0xAB }}},
                                                                          {49, {{ 0x18, 0x50, 0x1D, 0xDA }}},
                                                                          {50, {{ 0xE2, 0x75, 0x7E, 0x4F }}},
                                                                          {51, {{ 0x74, 0x1, 0x90, 0x5A }}},
                                                                          {52, {{ 0xCA, 0xFA, 0xAA, 0xE3 }}},
                                                                          {53, {{ 0xE4, 0xD5, 0x9B, 0x34 }}},
                                                                          {54, {{ 0x9A, 0xDF, 0x6A, 0xCE }}},
                                                                          {55, {{ 0xBD, 0x10, 0x19, 0xD }}},
                                                                          {56, {{ 0xFE, 0x48, 0x90, 0xD1 }}},
                                                                          {57, {{ 0xE6, 0x18, 0x8D, 0xB }}},
                                                                          {58, {{ 0x4, 0x6D, 0xF3, 0x44 }}},
                                                                          {59, {{ 0x70, 0x6C, 0x63, 0x1E }}},
                                                                      }}),
    };

    for (auto& item : KeyExpansionTestData) {
        LOG(INFO) << "Test: " << PARAM(0);
        AES::KeySchedule keys = AES::keyExpansion(&PARAM(1));
        AES::KeySchedule expected = PARAM(2);
        ASSERT_EQ(expected, keys);
    }
}
TEST(AESTest, AddRoundKey)
{
    // Simple test with test data from FIPS.197 p.33 and 34
    // round 1 and round 6 are tested
    AES::Key key = {{
                        0x2b, 0x7e, 0x15, 0x16,
                        0x28, 0xae, 0xd2, 0xa6,
                        0xab, 0xf7, 0x15, 0x88,
                        0x09, 0xcf, 0x4f, 0x3c
                    }};
    AES::KeySchedule schedule = AES::keyExpansion(&key);
    AES::State state = {{
        {{ 0x04, 0x66, 0x81, 0xe5 }},
        {{ 0xe0, 0xcb, 0x19, 0x9a }},
        {{ 0x48, 0xf8, 0xd3, 0x7a }},
        {{ 0x28, 0x06, 0x26, 0x4c }},
    }};
    AES::State expected2 = {{
        {{ 0xa4, 0x9c, 0x7f, 0xf2 }},
        {{ 0x68, 0x9f, 0x35, 0x2b }},
        {{ 0x6b, 0x5b, 0xea, 0x43 }},
        {{ 0x02, 0x6a, 0x50, 0x49 }},
    }};
    AES::State expected7 = {{
        {{ 0x26, 0x0e, 0x2e, 0x17 }},
        {{ 0x3d, 0x41, 0xb7, 0x7d }},
        {{ 0xe8, 0x64, 0x72, 0xa9 }},
        {{ 0xfd, 0xd2, 0x8b, 0x25 }},
    }};
    AES::addRoundKey(&state, &schedule, 1);
    ASSERT_EQ(expected2, state);

    state = {{
        {{ 0x4b, 0x86, 0x8d, 0x6d }},
        {{ 0x2c, 0x4a, 0x89, 0x80 }},
        {{ 0x33, 0x9d, 0xf4, 0xe8 }},
        {{ 0x37, 0xd2, 0x18, 0xd8 }},
    }};
    AES::addRoundKey(&state, &schedule, 6);
    ASSERT_EQ(expected7, state);
}

TEST(AESTest, RawCipher)
{

    // FIPS. 197 p. 33
    AES::ByteArray input = {{
                                0x32, 0x43, 0xf6, 0xa8,
                                0x88, 0x5a, 0x30, 0x8d,
                                0x31, 0x31, 0x98, 0xa2,
                                0xe0, 0x37, 0x07, 0x34
                            }};

    AES::Key key = {{
                        0x2b, 0x7e, 0x15, 0x16,
                        0x28, 0xae, 0xd2, 0xa6,
                        0xab, 0xf7, 0x15, 0x88,
                        0x09, 0xcf, 0x4f, 0x3c
                    }};

    AES::ByteArray expected = {{
                                   0x39, 0x25, 0x84, 0x1d,
                                   0x02, 0xdc, 0x09, 0xfb,
                                   0xdc, 0x11, 0x85, 0x97,
                                   0x19, 0x6a, 0x0b, 0x32
                               }};

    AES::ByteArray output = AES::cipher(input, &key);
    ASSERT_EQ(expected, output);

}
}

#endif // AES_TEST_H
