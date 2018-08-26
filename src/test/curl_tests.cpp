// Copyright (c) 2018 The COLX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "curl.h"

#include <string>
#include <fstream>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem/operations.hpp>

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(curl_tests)


BOOST_AUTO_TEST_CASE(curl_getredirect_test)
{
    string err1, out1;
    BOOST_CHECK(CURLGetRedirect("https://github.com/ColossusCoinXT/ColossusCoinXT/releases/latest", out1, err1));
    BOOST_CHECK_MESSAGE(err1.empty(), err1);
    BOOST_CHECK(!out1.empty());

    string err2, out2;
    BOOST_CHECK(!CURLGetRedirect("https://www.google.com", out2, err2));
    BOOST_CHECK(!err2.empty());
    BOOST_CHECK_MESSAGE(out2.empty(), out2);
}

BOOST_AUTO_TEST_CASE(curl_download_test)
{
    const CUrl url = "https://github.com/ColossusCoinXT/ColossusCoinXT/releases/download/v1.1.0_qt_downgrade/colx-1.1.0.tar.gz";
    const string tmpFile("download.tmp");
    auto ProgressFn = [](double total, double now) { return 0; };
    string buff, err;

    BOOST_REQUIRE_MESSAGE(CURLDownloadToMem(url, ProgressFn, buff, err), err);
    BOOST_REQUIRE_MESSAGE(CURLDownloadToFile(url, tmpFile, ProgressFn, err), err);

    std::ifstream f(tmpFile);
    std::string filebuff((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    BOOST_CHECK(buff == filebuff);

    filesystem::remove(tmpFile);
}

BOOST_AUTO_TEST_SUITE_END()
