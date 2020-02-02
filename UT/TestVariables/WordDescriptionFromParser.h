#pragma once

#include "wordsDb/wordsDescriptionsDb/Description.h"

using namespace wordsDb::wordsDescriptionsDb;

const DefinitionsWithExamples definitionsWithExamples{
    {"to go or come after and bring or take back", Example{"fetch a doctor"}},
    {"derive, deduce", Example{"fetch analogies from nature"}},
    {"to cause to come", Example{"one shot fetched down"}},
    {"to bring in (a price or similar return) : realize",
     Example{"The hogs fetched a good price at the market."}},
    {"interest, attract",
     Example{"… he doesn't fetch the girls like William …"}},
    {"to give (a blow) by striking : deal",
     Example{"fetch him a clip on the chin"}},
    {"bring about, accomplish", boost::none},
    {"to take in : draw", Example{"sat fetching her breath in dry sobs"}},
    {"to bring forth : heave", Example{"fetch a sigh"}},
    {"to reach by sailing especially against the wind or tide",
     Example{"fetch the harbor before the storm breaks"}},
    {"to arrive at : reach", Example{"fetched home after a long ride"}},
    {"to get and bring something", boost::none},
    {"to retrieve killed game", boost::none},
    {"to take a roundabout way : circle", boost::none},
    {"to hold a course on a body of water", Example{"fetch to windward"}},
    {"veer", boost::none},
    {"trick, stratagem", boost::none},
    {"an act or instance of fetching", boost::none},
    {"the distance along open water or land over which the wind blows",
     boost::none},
    {"the distance traversed by waves without obstruction", boost::none},
    {"doppelgänger sense 2", boost::none},
    {"to go after and bring back (someone or something)", boost::none},
    {"to be sold for (an amount of money)", boost::none},
    {"to go after and bring back", boost::none},
    {"to bring as a price : sell for",
     Example{"The artwork will fetch a high price."}},
};

const Sentences sentences{
    "If you throw the ball the dog will fetch it.",
    "Hunting dogs are trained to fetch.",
    "This table should fetch quite a bit at auction.",
    "The house fetched more than we expected.",
};
const Description wordDescriptionFromParser{definitionsWithExamples, sentences};
