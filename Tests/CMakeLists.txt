set (CMAKE_CXX_STANDARD 20)

link_libraries(${CMAKE_PROJECT_NAME})

#pass
# add_executable(firstTest_bin firstTest.cpp)
# add_test(firstTest firstTest_bin)

#fail
# add_executable(secondTest_bin secondTest.cpp)
# add_test(secondTest secondTest_bin)

# add_executable(test_md_parseLine_bin test_md_parseLine.cpp)
# add_test(test_md_parseLine test_md_parseLine_bin)
# set_tests_properties(test_md_parseLine  PROPERTIES FIXTURES_SETUP       fix_PARSE_LINE_OK)
# # set fixture PARSE_LINE_OK so that other tests can rely on it

# add_executable(test_md_slugify_bin test_md_slugify.cpp)
# add_test(test_md_slugify test_md_slugify_bin)
# set_tests_properties(test_md_slugify    PROPERTIES FIXTURES_SETUP       fix_SLUG_ONCE_OK)

# add_executable(test_md_slugifyList_bin test_md_slugifyList.cpp)
# add_test(test_md_slugifyList test_md_slugifyList_bin)
# set_tests_properties(test_md_slugifyList    PROPERTIES FIXTURES_REQUIRED    fix_SLUG_ONCE_OK)
# set_tests_properties(test_md_slugifyList    PROPERTIES FIXTURES_SETUP       fix_SLUG_OK)




# Don't run this test if we can't parse a line or get a title list slug
# add_executable(test_md_parseStr_bin test_md_parseStr.cpp)
# add_test(test_md_parseStr test_md_parseStr_bin)
# set_tests_properties(test_md_parseStr   PROPERTIES FIXTURES_REQUIRED    "fix_PARSE_LINE_OK;fix_SLUG_OK")
# set_tests_properties(test_md_parseStr   PROPERTIES FIXTURES_SETUP       fix_PARSE_STR_OK)

# add_executable(test_md_parseFile_bin test_md_parseFile.cpp)
# add_test(test_md_parseFile test_md_parseFile_bin PROPERTIES DEPENDS test_md_parseStr_bin)
# set_tests_properties(test_md_parseFile  PROPERTIES FIXTURES_REQUIRED   fix_PARSE_STR_OK)


# add_executable(test_md_insertTableInFile_bin test_md_insertTableInFile.cpp)
# add_test(test_md_insertTableInFile test_md_insertTableInFile_bin)