#include <gtest/gtest.h>

#include <libSimpleScanner.h>

/**
 * @brief Construct a new TEST object
 * @todo add unit tests for the parser
 */
TEST(ring_buffer, test_that_scanner_works)
{
    ss_data_t data;
    std::string long_str = "LONG TYPE: name=london,51.5072,0.1276";
    

    bool er = ss_parse_message(&data,(char*) long_str.c_str());
    ASSERT_EQ(true,er);

    ASSERT_EQ(SS_LONG_MESSAGE,data.type);
    ASSERT_STREQ("london",data.data.long_data.name);

    ASSERT_EQ(51.5072,data.data.long_data.latitude);
    ASSERT_EQ(0.1276,data.data.long_data.longitude);


    std::string  special_str = "SPECIAL TYPE: \"external system one\",2.675421345,-1.675,north,al:25,coosign:none,alert";
    er = ss_parse_message(&data,(char*) special_str.c_str());
    
    ASSERT_EQ(true,er);

    ASSERT_EQ(SS_SPECIAL_MESSAGE,data.type);
    ASSERT_STREQ("\"external system one\"", data.data.special_data.name);

    ASSERT_EQ(2.675421345,data.data.special_data.latitude);
    ASSERT_EQ(-1.675,data.data.special_data.longitude);

    ASSERT_EQ(4,data.data.special_data.num_special);
    ASSERT_STREQ("north",data.data.special_data.special[0]);
    ASSERT_STREQ("al:25",data.data.special_data.special[1]);
    ASSERT_STREQ("coosign:none",data.data.special_data.special[2]);
    ASSERT_STREQ("alert",data.data.special_data.special[3]);

    std::string not_special_str = "NOT SPECIAL TYPE: \"external system two\",\"Ormskirk research\",\"active\"";
    er = ss_parse_message(&data,(char*) not_special_str.c_str());

    ASSERT_EQ(true,er);
    ASSERT_EQ(SS_NOT_SPECIAL_MESSAGE,data.type);

    ASSERT_STREQ("\"external system two\"", data.data.not_special_data.name);
    ASSERT_STREQ("\"Ormskirk research\"", data.data.not_special_data.place);
    ASSERT_STREQ("\"active\"", data.data.not_special_data.status);
}
