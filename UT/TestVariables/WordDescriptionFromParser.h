#pragma once

#include "wordsDb/descriptionsDb/Description.h"

using namespace wordsDb::descriptionsDb;

const DefinitionsWithExamples definitionsWithExamples{
        {"the alcoholic fermented juice of fresh grapes used as a beverage", boost::none},
        {"wine or a substitute used in Christian communion services", boost::none},
        {"the alcoholic usually fermented juice of a plant product (such as a fruit) used as a beverage",
         Example{"blackberry wine"}},
        {"something that invigorates or intoxicates", boost::none},
        {"a dark red", boost::none},
        {"to drink wine", boost::none},
        {"to give wine to", Example{"wined and dined his friends"}},
        {"an alcoholic drink made from the juice of grapes", boost::none},
        {"an alcoholic drink made from plants or fruits other than grapes", boost::none},
        {"a dark reddish-purple color", boost::none},
        {"an alcoholic beverage made from the fermented juice of grapes", boost::none},
        {"an alcoholic beverage made from the usually fermented juice of fruits (as peaches) other than grapes",
         boost::none},
        {"fermented grape juice containing varying percentages of alcohol together with ethers and esters that give it bouquet and flavor",
         boost::none},
        {"a pharmaceutical preparation using wine as a vehicle", boost::none}
};

const Sentences sentences{
        "Plus a bountiful selection of French wines to drink and lots of shiny equipment to use.",
        "In addition to beer, a selection of local and national wines will be offered..",
        "Who doesn't love delicious food paired with your favorite wine?",
        "Rucker continues to cook with wine, but isn\xE2\x80\x99t tempted by it.",
        "The tasting fee at Maison Bleue is $15, with wines generally in the $60-$65 range.",
        "The Beer Garden will be sponsored by Door Peninsula Winery, which will sell its specialty Halloween wines.",
        "Almost everybody works for the local Asconi winery, and almost everyone distills their own wine.",
        "Ticket price will include samples of wines made in Virginia.",
        "Louisiana Purchase will wine and dine guests at its second Sicilian Chefs Table dinner party.",
        "Patrons can wine and dine on the small front patio, which captures the authentic neighborhood charm near the heart of the city.",
        "Purists, like Hovhannisyan, insist that fresh lavash\xE2\x80\x94torn and folded for easy scooping\xE2\x80\x94is the only acceptable utensil for eating khash, and that vodka, never wine or beer, is its only worthy sidekick.",
        "Purchases of growlers and kegs include a chance to wine one of four $50 Beer Engine gift cards.",
        "Cocktails frequently lose out to wine and beer at home because so much of what\xE2\x80\x99s on menus requires more effort and expense than non-professionals are willing to commit to.",
        "Pence\xE2\x80\x99s press secretary\xE2\x80\x99s comment comes after the Times reported last week that the vice president has been wineing and dining influential Republican donors at the Naval Observatory.",
        "SANTA ROSA, Calif. \xE2\x80\x94 In the heart of Northern California\xE2\x80\x99s wine country, a civil engineer turned marijuana entrepreneur is adding a new dimension to the art of matching fine wines with gourmet food: cannabis and wine pairing dinners."
};
const Description wordDescriptionFromParser{definitionsWithExamples, sentences};
