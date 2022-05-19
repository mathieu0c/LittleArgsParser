#pragma once

#include <iostream>

#ifndef NO_ERROR_LOG
#define ENABLE_ERROR_LOG
#endif

#define ENABLE_LOG

#ifdef ENABLE_LOG

    #define LOG(x) std::cout<<x
    #define LOGL(x) LOG(x)<<"\n"
    #define LOGP(x) std::cout<<_FILE_<<" - <"<<__func__<<"> l."<<__LINE__<<" : "<<x
    #define LOGPL(x) LOGP(x)<<"\n"

    #include <regex>
    #include <string>
    #include <string_view>
    inline
    void logRegex(const std::string& rxTxt,const std::string& txt){
        const std::regex base_regex(rxTxt,std::regex_constants::extended);
        std::smatch pieces_match;
        LOGPL("Logging regex <"<<rxTxt<<"> :");
        if (std::regex_search(txt, pieces_match, base_regex)) {
            for (size_t i = 0; i < pieces_match.size(); ++i) {
                LOGL("************************************************ - "<<i);
                std::ssub_match sub_match = pieces_match[i];
                std::string piece = sub_match.str();
                LOGL(piece);
            }   
        }
        else
        {
            LOGL("No match");
        }
    }

    #define LOG_REGEX(rxTxt,txt) logRegex(rxTxt,txt)

#else

    #define LOG(x);
    #define LOGL(x);
    #define LOGP(x);
    #define LOGPL(x);

#endif

#ifdef ENABLE_ERROR_LOG
    #define RAWEL(x) std::cerr<<x
    #define LOGE(x) std::cerr<<"ERR:"<<_FILE_<<":"<<__PRETTY_FUNCTION__<<": l."<<__LINE__<<" : "<<x
    #define LOGEL(x) LOGE(x)<<"\n"
#else
    #define LOGE(x);
    #define RAWEL(x);
    #define LOGEL(x);
#endif


