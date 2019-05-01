#include <boost/phoenix/object/construct.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/include/lex.hpp>

#include "url_parser.hpp"

std::tuple<std::string,std::string,std::string,std::string> parse_url(std::string url) {

    std::tuple<std::string,std::string,std::string,std::string> segments;

    using boost::spirit::lex::_start;
    using boost::spirit::lex::_end;

    if( boost::spirit::x3::phrase_parse(url.begin(),
                                        url.end(),
            (
                -(+boost::spirit::x3::alpha >> "://") [([&segments](auto &ctx) mutable {std::get<0>(segments) = boost::optional<std::string>(boost::spirit::x3::_attr(ctx)).value();})] >>
                (+(boost::spirit::x3::char_ - (boost::spirit::x3::char_("[/?]"))))[([&segments](auto &ctx) mutable {std::get<1>(segments) = boost::optional<std::string>(boost::spirit::x3::_attr(ctx)).value();})] >>
                -(
                    (+(boost::spirit::x3::char_ - boost::spirit::x3::char_("?")))[([&segments](auto &ctx) mutable {std::get<2>(segments) = boost::optional<std::string>(boost::spirit::x3::_attr(ctx)).value();})] >>
                    -(
                        ((+boost::spirit::x3::char_)[([&segments](auto &ctx) mutable {std::get<3>(segments) = boost::optional<std::string>(boost::spirit::x3::_attr(ctx)).value();})])
                    )
                )
            ), boost::spirit::x3::space))
        return segments;

    std::cout << "Failed to parse.\n";

    using std::string_literals::operator""s;
    return {""s,""s,""s,""s};
}