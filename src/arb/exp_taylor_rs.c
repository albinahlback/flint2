/*
    Copyright (C) 2014 Fredrik Johansson

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "arb.h"
#include "mpn_extras.h"

/* See verify_taylor.py for code to generate tables and
   proof of correctness */

#define TMP_ALLOC_LIMBS(size) TMP_ALLOC((size) * sizeof(ulong))

#define FACTORIAL_TAB_SIZE 288

#if FLINT_BITS == 64

const ulong factorial_tab_numer[FACTORIAL_TAB_SIZE] = {
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(1216451004088320000),
    UWORD(405483668029440000),
    UWORD(101370917007360000),
    UWORD(20274183401472000),
    UWORD(3379030566912000),
    UWORD(482718652416000),
    UWORD(60339831552000),
    UWORD(6704425728000),
    UWORD(670442572800),
    UWORD(60949324800),
    UWORD(5079110400),
    UWORD(390700800),
    UWORD(27907200),
    UWORD(1860480),
    UWORD(116280),
    UWORD(6840),
    UWORD(380),
    UWORD(20),
    UWORD(1),
    UWORD(169958063987712000),
    UWORD(7725366544896000),
    UWORD(335885501952000),
    UWORD(13995229248000),
    UWORD(559809169920),
    UWORD(21531121920),
    UWORD(797448960),
    UWORD(28480320),
    UWORD(982080),
    UWORD(32736),
    UWORD(1056),
    UWORD(33),
    UWORD(1),
    UWORD(405179306820288000),
    UWORD(11576551623436800),
    UWORD(321570878428800),
    UWORD(8691104822400),
    UWORD(228713284800),
    UWORD(5864443200),
    UWORD(146611080),
    UWORD(3575880),
    UWORD(85140),
    UWORD(1980),
    UWORD(45),
    UWORD(1),
    UWORD(129210868410624000),
    UWORD(2749167412992000),
    UWORD(57274321104000),
    UWORD(1168863696000),
    UWORD(23377273920),
    UWORD(458377920),
    UWORD(8814960),
    UWORD(166320),
    UWORD(3080),
    UWORD(56),
    UWORD(1),
    UWORD(13431688016947200),
    UWORD(231580827878400),
    UWORD(3925098777600),
    UWORD(65418312960),
    UWORD(1072431360),
    UWORD(17297280),
    UWORD(274560),
    UWORD(4290),
    UWORD(66),
    UWORD(1),
    UWORD(51698307350592000),
    UWORD(760269225744000),
    UWORD(11018394576000),
    UWORD(157405636800),
    UWORD(2216980800),
    UWORD(30791400),
    UWORD(421800),
    UWORD(5700),
    UWORD(76),
    UWORD(1),
    UWORD(166872705665702400),
    UWORD(2139393662380800),
    UWORD(27080932435200),
    UWORD(338511655440),
    UWORD(4179156240),
    UWORD(50965320),
    UWORD(614040),
    UWORD(7310),
    UWORD(86),
    UWORD(1),
    UWORD(4900933563926400),
    UWORD(55692426862800),
    UWORD(625757605200),
    UWORD(6952862280),
    UWORD(76405080),
    UWORD(830490),
    UWORD(8930),
    UWORD(95),
    UWORD(1),
    UWORD(10385445095625600),
    UWORD(107066444284800),
    UWORD(1092514737600),
    UWORD(11035502400),
    UWORD(110355024),
    UWORD(1092624),
    UWORD(10712),
    UWORD(104),
    UWORD(1),
    UWORD(20632508204394240),
    UWORD(194646303815040),
    UWORD(1819124334720),
    UWORD(16843743840),
    UWORD(154529760),
    UWORD(1404816),
    UWORD(12656),
    UWORD(113),
    UWORD(1),
    UWORD(38823716505974400),
    UWORD(337597534834560),
    UWORD(2910323576160),
    UWORD(24874560480),
    UWORD(210801360),
    UWORD(1771440),
    UWORD(14762),
    UWORD(122),
    UWORD(1),
    UWORD(69746158460160000),
    UWORD(562469019840000),
    UWORD(4499752158720),
    UWORD(35712318720),
    UWORD(281199360),
    UWORD(2196870),
    UWORD(17030),
    UWORD(131),
    UWORD(1),
    UWORD(120384786168259200),
    UWORD(905148768182400),
    UWORD(6754841553600),
    UWORD(50035863360),
    UWORD(367910760),
    UWORD(2685480),
    UWORD(19460),
    UWORD(140),
    UWORD(1),
    UWORD(1346749373249280),
    UWORD(9484150515840),
    UWORD(66322730880),
    UWORD(460574520),
    UWORD(3176376),
    UWORD(21756),
    UWORD(148),
    UWORD(1),
    UWORD(1961463552048000),
    UWORD(13076423680320),
    UWORD(86598832320),
    UWORD(569729160),
    UWORD(3723720),
    UWORD(24180),
    UWORD(156),
    UWORD(1),
    UWORD(2802505908948480),
    UWORD(17737379170560),
    UWORD(111555843840),
    UWORD(697224024),
    UWORD(4330584),
    UWORD(26732),
    UWORD(164),
    UWORD(1),
    UWORD(3935446603320960),
    UWORD(23707509658560),
    UWORD(141961135680),
    UWORD(845006760),
    UWORD(5000040),
    UWORD(29412),
    UWORD(172),
    UWORD(1),
    UWORD(5440248896544000),
    UWORD(31265798256000),
    UWORD(178661704320),
    UWORD(1015123320),
    UWORD(5735160),
    UWORD(32220),
    UWORD(180),
    UWORD(1),
    UWORD(7413519413139840),
    UWORD(40733623149120),
    UWORD(222588104640),
    UWORD(1209717960),
    UWORD(6539016),
    UWORD(35156),
    UWORD(188),
    UWORD(1),
    UWORD(9970981685683200),
    UWORD(52478850977280),
    UWORD(274758382080),
    UWORD(1431033240),
    UWORD(7414680),
    UWORD(38220),
    UWORD(196),
    UWORD(1),
    UWORD(13250183553129600),
    UWORD(66920118955200),
    UWORD(336282004800),
    UWORD(1681410024),
    UWORD(8365224),
    UWORD(41412),
    UWORD(204),
    UWORD(1),
    UWORD(17413448982209280),
    UWORD(84531305738880),
    UWORD(408363795840),
    UWORD(1963287480),
    UWORD(9393720),
    UWORD(44732),
    UWORD(212),
    UWORD(1),
    UWORD(22651084881532800),
    UWORD(105846191035200),
    UWORD(492307865280),
    UWORD(2279203080),
    UWORD(10503240),
    UWORD(48180),
    UWORD(220),
    UWORD(1),
    UWORD(29184853478054400),
    UWORD(131463303955200),
    UWORD(589521542400),
    UWORD(2631792600),
    UWORD(11696856),
    UWORD(51756),
    UWORD(228),
    UWORD(1),
    UWORD(37271720825539200),
    UWORD(162050960111040),
    UWORD(701519307840),
    UWORD(3023790120),
    UWORD(12977640),
    UWORD(55460),
    UWORD(236),
    UWORD(1),
    UWORD(47207892014680320),
    UWORD(198352487456640),
    UWORD(829926725760),
    UWORD(3458028024),
    UWORD(14348664),
    UWORD(59292),
    UWORD(244),
    UWORD(1),
    UWORD(59333143654512000),
    UWORD(241191640872000),
    UWORD(976484376000),
    UWORD(3937437000),
    UWORD(15813000),
    UWORD(63252),
    UWORD(252),
    UWORD(1),
    UWORD(284751785364480),
    UWORD(1121070021120),
    UWORD(4396353024),
    UWORD(17173254),
    UWORD(66822),
    UWORD(259),
    UWORD(1),
    UWORD(334679402201760),
    UWORD(1282296560160),
    UWORD(4894261680),
    UWORD(18609360),
    UWORD(70490),
    UWORD(266),
    UWORD(1),
    UWORD(391698294099840),
    UWORD(1461560798880),
    UWORD(5433311520),
    UWORD(20123376),
    UWORD(74256),
    UWORD(273),
    UWORD(1),
    UWORD(456592291848000),
    UWORD(1660335606720),
    UWORD(6015708720),
    UWORD(21717360),
    UWORD(78120),
    UWORD(280),
    UWORD(1),
    UWORD(530208485286480),
    UWORD(1880171933640),
    UWORD(6643717080),
    UWORD(23393370),
    UWORD(82082),
    UWORD(287),
    UWORD(1),
};

const ulong factorial_tab_denom[FACTORIAL_TAB_SIZE] = {
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(2432902008176640000),
    UWORD(3569119343741952000),
    UWORD(3569119343741952000),
    UWORD(3569119343741952000),
    UWORD(3569119343741952000),
    UWORD(3569119343741952000),
    UWORD(3569119343741952000),
    UWORD(3569119343741952000),
    UWORD(3569119343741952000),
    UWORD(3569119343741952000),
    UWORD(3569119343741952000),
    UWORD(3569119343741952000),
    UWORD(3569119343741952000),
    UWORD(3569119343741952000),
    UWORD(13776096431889792000),
    UWORD(13776096431889792000),
    UWORD(13776096431889792000),
    UWORD(13776096431889792000),
    UWORD(13776096431889792000),
    UWORD(13776096431889792000),
    UWORD(13776096431889792000),
    UWORD(13776096431889792000),
    UWORD(13776096431889792000),
    UWORD(13776096431889792000),
    UWORD(13776096431889792000),
    UWORD(13776096431889792000),
    UWORD(5943699946888704000),
    UWORD(5943699946888704000),
    UWORD(5943699946888704000),
    UWORD(5943699946888704000),
    UWORD(5943699946888704000),
    UWORD(5943699946888704000),
    UWORD(5943699946888704000),
    UWORD(5943699946888704000),
    UWORD(5943699946888704000),
    UWORD(5943699946888704000),
    UWORD(5943699946888704000),
    UWORD(765606216965990400),
    UWORD(765606216965990400),
    UWORD(765606216965990400),
    UWORD(765606216965990400),
    UWORD(765606216965990400),
    UWORD(765606216965990400),
    UWORD(765606216965990400),
    UWORD(765606216965990400),
    UWORD(765606216965990400),
    UWORD(765606216965990400),
    UWORD(3463786592489664000),
    UWORD(3463786592489664000),
    UWORD(3463786592489664000),
    UWORD(3463786592489664000),
    UWORD(3463786592489664000),
    UWORD(3463786592489664000),
    UWORD(3463786592489664000),
    UWORD(3463786592489664000),
    UWORD(3463786592489664000),
    UWORD(3463786592489664000),
    UWORD(12849198336259084800),
    UWORD(12849198336259084800),
    UWORD(12849198336259084800),
    UWORD(12849198336259084800),
    UWORD(12849198336259084800),
    UWORD(12849198336259084800),
    UWORD(12849198336259084800),
    UWORD(12849198336259084800),
    UWORD(12849198336259084800),
    UWORD(12849198336259084800),
    UWORD(426381220061596800),
    UWORD(426381220061596800),
    UWORD(426381220061596800),
    UWORD(426381220061596800),
    UWORD(426381220061596800),
    UWORD(426381220061596800),
    UWORD(426381220061596800),
    UWORD(426381220061596800),
    UWORD(426381220061596800),
    UWORD(997002729180057600),
    UWORD(997002729180057600),
    UWORD(997002729180057600),
    UWORD(997002729180057600),
    UWORD(997002729180057600),
    UWORD(997002729180057600),
    UWORD(997002729180057600),
    UWORD(997002729180057600),
    UWORD(997002729180057600),
    UWORD(2166413361461395200),
    UWORD(2166413361461395200),
    UWORD(2166413361461395200),
    UWORD(2166413361461395200),
    UWORD(2166413361461395200),
    UWORD(2166413361461395200),
    UWORD(2166413361461395200),
    UWORD(2166413361461395200),
    UWORD(2166413361461395200),
    UWORD(4425903681681081600),
    UWORD(4425903681681081600),
    UWORD(4425903681681081600),
    UWORD(4425903681681081600),
    UWORD(4425903681681081600),
    UWORD(4425903681681081600),
    UWORD(4425903681681081600),
    UWORD(4425903681681081600),
    UWORD(4425903681681081600),
    UWORD(8578777490599680000),
    UWORD(8578777490599680000),
    UWORD(8578777490599680000),
    UWORD(8578777490599680000),
    UWORD(8578777490599680000),
    UWORD(8578777490599680000),
    UWORD(8578777490599680000),
    UWORD(8578777490599680000),
    UWORD(8578777490599680000),
    UWORD(15890791774210214400),
    UWORD(15890791774210214400),
    UWORD(15890791774210214400),
    UWORD(15890791774210214400),
    UWORD(15890791774210214400),
    UWORD(15890791774210214400),
    UWORD(15890791774210214400),
    UWORD(15890791774210214400),
    UWORD(15890791774210214400),
    UWORD(189891661628148480),
    UWORD(189891661628148480),
    UWORD(189891661628148480),
    UWORD(189891661628148480),
    UWORD(189891661628148480),
    UWORD(189891661628148480),
    UWORD(189891661628148480),
    UWORD(189891661628148480),
    UWORD(292258069255152000),
    UWORD(292258069255152000),
    UWORD(292258069255152000),
    UWORD(292258069255152000),
    UWORD(292258069255152000),
    UWORD(292258069255152000),
    UWORD(292258069255152000),
    UWORD(292258069255152000),
    UWORD(439993427704911360),
    UWORD(439993427704911360),
    UWORD(439993427704911360),
    UWORD(439993427704911360),
    UWORD(439993427704911360),
    UWORD(439993427704911360),
    UWORD(439993427704911360),
    UWORD(439993427704911360),
    UWORD(649348689547958400),
    UWORD(649348689547958400),
    UWORD(649348689547958400),
    UWORD(649348689547958400),
    UWORD(649348689547958400),
    UWORD(649348689547958400),
    UWORD(649348689547958400),
    UWORD(649348689547958400),
    UWORD(941163059102112000),
    UWORD(941163059102112000),
    UWORD(941163059102112000),
    UWORD(941163059102112000),
    UWORD(941163059102112000),
    UWORD(941163059102112000),
    UWORD(941163059102112000),
    UWORD(941163059102112000),
    UWORD(1341847013778311040),
    UWORD(1341847013778311040),
    UWORD(1341847013778311040),
    UWORD(1341847013778311040),
    UWORD(1341847013778311040),
    UWORD(1341847013778311040),
    UWORD(1341847013778311040),
    UWORD(1341847013778311040),
    UWORD(1884515538594124800),
    UWORD(1884515538594124800),
    UWORD(1884515538594124800),
    UWORD(1884515538594124800),
    UWORD(1884515538594124800),
    UWORD(1884515538594124800),
    UWORD(1884515538594124800),
    UWORD(1884515538594124800),
    UWORD(2610286159966531200),
    UWORD(2610286159966531200),
    UWORD(2610286159966531200),
    UWORD(2610286159966531200),
    UWORD(2610286159966531200),
    UWORD(2610286159966531200),
    UWORD(2610286159966531200),
    UWORD(2610286159966531200),
    UWORD(3569757041352902400),
    UWORD(3569757041352902400),
    UWORD(3569757041352902400),
    UWORD(3569757041352902400),
    UWORD(3569757041352902400),
    UWORD(3569757041352902400),
    UWORD(3569757041352902400),
    UWORD(3569757041352902400),
    UWORD(4824681079766486400),
    UWORD(4824681079766486400),
    UWORD(4824681079766486400),
    UWORD(4824681079766486400),
    UWORD(4824681079766486400),
    UWORD(4824681079766486400),
    UWORD(4824681079766486400),
    UWORD(4824681079766486400),
    UWORD(6449852618650022400),
    UWORD(6449852618650022400),
    UWORD(6449852618650022400),
    UWORD(6449852618650022400),
    UWORD(6449852618650022400),
    UWORD(6449852618650022400),
    UWORD(6449852618650022400),
    UWORD(6449852618650022400),
    UWORD(8535224069048476800),
    UWORD(8535224069048476800),
    UWORD(8535224069048476800),
    UWORD(8535224069048476800),
    UWORD(8535224069048476800),
    UWORD(8535224069048476800),
    UWORD(8535224069048476800),
    UWORD(8535224069048476800),
    UWORD(11188270407479235840),
    UWORD(11188270407479235840),
    UWORD(11188270407479235840),
    UWORD(11188270407479235840),
    UWORD(11188270407479235840),
    UWORD(11188270407479235840),
    UWORD(11188270407479235840),
    UWORD(11188270407479235840),
    UWORD(14536620195355440000),
    UWORD(14536620195355440000),
    UWORD(14536620195355440000),
    UWORD(14536620195355440000),
    UWORD(14536620195355440000),
    UWORD(14536620195355440000),
    UWORD(14536620195355440000),
    UWORD(14536620195355440000),
    UWORD(72042201697213440),
    UWORD(72042201697213440),
    UWORD(72042201697213440),
    UWORD(72042201697213440),
    UWORD(72042201697213440),
    UWORD(72042201697213440),
    UWORD(72042201697213440),
    UWORD(87016644572457600),
    UWORD(87016644572457600),
    UWORD(87016644572457600),
    UWORD(87016644572457600),
    UWORD(87016644572457600),
    UWORD(87016644572457600),
    UWORD(87016644572457600),
    UWORD(104583444524657280),
    UWORD(104583444524657280),
    UWORD(104583444524657280),
    UWORD(104583444524657280),
    UWORD(104583444524657280),
    UWORD(104583444524657280),
    UWORD(104583444524657280),
    UWORD(125106287966352000),
    UWORD(125106287966352000),
    UWORD(125106287966352000),
    UWORD(125106287966352000),
    UWORD(125106287966352000),
    UWORD(125106287966352000),
    UWORD(125106287966352000),
    UWORD(148988584365500880),
    UWORD(148988584365500880),
    UWORD(148988584365500880),
    UWORD(148988584365500880),
    UWORD(148988584365500880),
    UWORD(148988584365500880),
    UWORD(148988584365500880),
};

#else

const ulong factorial_tab_numer[FACTORIAL_TAB_SIZE] = {
    UWORD(479001600),
    UWORD(479001600),
    UWORD(239500800),
    UWORD(79833600),
    UWORD(19958400),
    UWORD(3991680),
    UWORD(665280),
    UWORD(95040),
    UWORD(11880),
    UWORD(1320),
    UWORD(132),
    UWORD(12),
    UWORD(1),
    UWORD(19535040),
    UWORD(1395360),
    UWORD(93024),
    UWORD(5814),
    UWORD(342),
    UWORD(19),
    UWORD(1),
    UWORD(165765600),
    UWORD(7893600),
    UWORD(358800),
    UWORD(15600),
    UWORD(650),
    UWORD(26),
    UWORD(1),
    UWORD(24165120),
    UWORD(863040),
    UWORD(29760),
    UWORD(992),
    UWORD(32),
    UWORD(1),
    UWORD(60233040),
    UWORD(1771560),
    UWORD(50616),
    UWORD(1406),
    UWORD(38),
    UWORD(1),
    UWORD(2961840),
    UWORD(74046),
    UWORD(1806),
    UWORD(43),
    UWORD(1),
    UWORD(4669920),
    UWORD(103776),
    UWORD(2256),
    UWORD(48),
    UWORD(1),
    UWORD(7027800),
    UWORD(140556),
    UWORD(2756),
    UWORD(53),
    UWORD(1),
    UWORD(10182480),
    UWORD(185136),
    UWORD(3306),
    UWORD(58),
    UWORD(1),
    UWORD(14295960),
    UWORD(238266),
    UWORD(3906),
    UWORD(63),
    UWORD(1),
    UWORD(19545240),
    UWORD(300696),
    UWORD(4556),
    UWORD(68),
    UWORD(1),
    UWORD(26122320),
    UWORD(373176),
    UWORD(5256),
    UWORD(73),
    UWORD(1),
    UWORD(34234200),
    UWORD(456456),
    UWORD(6006),
    UWORD(78),
    UWORD(1),
    UWORD(44102880),
    UWORD(551286),
    UWORD(6806),
    UWORD(83),
    UWORD(1),
    UWORD(635970),
    UWORD(7482),
    UWORD(87),
    UWORD(1),
    UWORD(728910),
    UWORD(8190),
    UWORD(91),
    UWORD(1),
    UWORD(830490),
    UWORD(8930),
    UWORD(95),
    UWORD(1),
    UWORD(941094),
    UWORD(9702),
    UWORD(99),
    UWORD(1),
    UWORD(1061106),
    UWORD(10506),
    UWORD(103),
    UWORD(1),
    UWORD(1190910),
    UWORD(11342),
    UWORD(107),
    UWORD(1),
    UWORD(1330890),
    UWORD(12210),
    UWORD(111),
    UWORD(1),
    UWORD(1481430),
    UWORD(13110),
    UWORD(115),
    UWORD(1),
    UWORD(1642914),
    UWORD(14042),
    UWORD(119),
    UWORD(1),
    UWORD(1815726),
    UWORD(15006),
    UWORD(123),
    UWORD(1),
    UWORD(2000250),
    UWORD(16002),
    UWORD(127),
    UWORD(1),
    UWORD(2196870),
    UWORD(17030),
    UWORD(131),
    UWORD(1),
    UWORD(2405970),
    UWORD(18090),
    UWORD(135),
    UWORD(1),
    UWORD(2627934),
    UWORD(19182),
    UWORD(139),
    UWORD(1),
    UWORD(2863146),
    UWORD(20306),
    UWORD(143),
    UWORD(1),
    UWORD(3111990),
    UWORD(21462),
    UWORD(147),
    UWORD(1),
    UWORD(3374850),
    UWORD(22650),
    UWORD(151),
    UWORD(1),
    UWORD(3652110),
    UWORD(23870),
    UWORD(155),
    UWORD(1),
    UWORD(3944154),
    UWORD(25122),
    UWORD(159),
    UWORD(1),
    UWORD(4251366),
    UWORD(26406),
    UWORD(163),
    UWORD(1),
    UWORD(4574130),
    UWORD(27722),
    UWORD(167),
    UWORD(1),
    UWORD(4912830),
    UWORD(29070),
    UWORD(171),
    UWORD(1),
    UWORD(5267850),
    UWORD(30450),
    UWORD(175),
    UWORD(1),
    UWORD(5639574),
    UWORD(31862),
    UWORD(179),
    UWORD(1),
    UWORD(6028386),
    UWORD(33306),
    UWORD(183),
    UWORD(1),
    UWORD(6434670),
    UWORD(34782),
    UWORD(187),
    UWORD(1),
    UWORD(6858810),
    UWORD(36290),
    UWORD(191),
    UWORD(1),
    UWORD(7301190),
    UWORD(37830),
    UWORD(195),
    UWORD(1),
    UWORD(7762194),
    UWORD(39402),
    UWORD(199),
    UWORD(1),
    UWORD(8242206),
    UWORD(41006),
    UWORD(203),
    UWORD(1),
    UWORD(8741610),
    UWORD(42642),
    UWORD(207),
    UWORD(1),
    UWORD(9260790),
    UWORD(44310),
    UWORD(211),
    UWORD(1),
    UWORD(9800130),
    UWORD(46010),
    UWORD(215),
    UWORD(1),
    UWORD(10360014),
    UWORD(47742),
    UWORD(219),
    UWORD(1),
    UWORD(10940826),
    UWORD(49506),
    UWORD(223),
    UWORD(1),
    UWORD(11542950),
    UWORD(51302),
    UWORD(227),
    UWORD(1),
    UWORD(12166770),
    UWORD(53130),
    UWORD(231),
    UWORD(1),
    UWORD(12812670),
    UWORD(54990),
    UWORD(235),
    UWORD(1),
    UWORD(13481034),
    UWORD(56882),
    UWORD(239),
    UWORD(1),
    UWORD(14172246),
    UWORD(58806),
    UWORD(243),
    UWORD(1),
    UWORD(14886690),
    UWORD(60762),
    UWORD(247),
    UWORD(1),
    UWORD(15624750),
    UWORD(62750),
    UWORD(251),
    UWORD(1),
    UWORD(16386810),
    UWORD(64770),
    UWORD(255),
    UWORD(1),
    UWORD(66306),
    UWORD(258),
    UWORD(1),
    UWORD(67860),
    UWORD(261),
    UWORD(1),
    UWORD(69432),
    UWORD(264),
    UWORD(1),
    UWORD(71022),
    UWORD(267),
    UWORD(1),
    UWORD(72630),
    UWORD(270),
    UWORD(1),
    UWORD(74256),
    UWORD(273),
    UWORD(1),
    UWORD(75900),
    UWORD(276),
    UWORD(1),
    UWORD(77562),
    UWORD(279),
    UWORD(1),
    UWORD(79242),
    UWORD(282),
    UWORD(1),
    UWORD(80940),
    UWORD(285),
    UWORD(1),
    UWORD(82656),
    UWORD(288),
};

const ulong factorial_tab_denom[FACTORIAL_TAB_SIZE] = {
    UWORD(479001600),
    UWORD(479001600),
    UWORD(479001600),
    UWORD(479001600),
    UWORD(479001600),
    UWORD(479001600),
    UWORD(479001600),
    UWORD(479001600),
    UWORD(479001600),
    UWORD(479001600),
    UWORD(479001600),
    UWORD(479001600),
    UWORD(479001600),
    UWORD(253955520),
    UWORD(253955520),
    UWORD(253955520),
    UWORD(253955520),
    UWORD(253955520),
    UWORD(253955520),
    UWORD(253955520),
    UWORD(3315312000),
    UWORD(3315312000),
    UWORD(3315312000),
    UWORD(3315312000),
    UWORD(3315312000),
    UWORD(3315312000),
    UWORD(3315312000),
    UWORD(652458240),
    UWORD(652458240),
    UWORD(652458240),
    UWORD(652458240),
    UWORD(652458240),
    UWORD(652458240),
    UWORD(1987690320),
    UWORD(1987690320),
    UWORD(1987690320),
    UWORD(1987690320),
    UWORD(1987690320),
    UWORD(1987690320),
    UWORD(115511760),
    UWORD(115511760),
    UWORD(115511760),
    UWORD(115511760),
    UWORD(115511760),
    UWORD(205476480),
    UWORD(205476480),
    UWORD(205476480),
    UWORD(205476480),
    UWORD(205476480),
    UWORD(344362200),
    UWORD(344362200),
    UWORD(344362200),
    UWORD(344362200),
    UWORD(344362200),
    UWORD(549853920),
    UWORD(549853920),
    UWORD(549853920),
    UWORD(549853920),
    UWORD(549853920),
    UWORD(843461640),
    UWORD(843461640),
    UWORD(843461640),
    UWORD(843461640),
    UWORD(843461640),
    UWORD(1250895360),
    UWORD(1250895360),
    UWORD(1250895360),
    UWORD(1250895360),
    UWORD(1250895360),
    UWORD(1802440080),
    UWORD(1802440080),
    UWORD(1802440080),
    UWORD(1802440080),
    UWORD(1802440080),
    UWORD(2533330800),
    UWORD(2533330800),
    UWORD(2533330800),
    UWORD(2533330800),
    UWORD(2533330800),
    UWORD(3484127520),
    UWORD(3484127520),
    UWORD(3484127520),
    UWORD(3484127520),
    UWORD(3484127520),
    UWORD(53421480),
    UWORD(53421480),
    UWORD(53421480),
    UWORD(53421480),
    UWORD(64144080),
    UWORD(64144080),
    UWORD(64144080),
    UWORD(64144080),
    UWORD(76405080),
    UWORD(76405080),
    UWORD(76405080),
    UWORD(76405080),
    UWORD(90345024),
    UWORD(90345024),
    UWORD(90345024),
    UWORD(90345024),
    UWORD(106110600),
    UWORD(106110600),
    UWORD(106110600),
    UWORD(106110600),
    UWORD(123854640),
    UWORD(123854640),
    UWORD(123854640),
    UWORD(123854640),
    UWORD(143736120),
    UWORD(143736120),
    UWORD(143736120),
    UWORD(143736120),
    UWORD(165920160),
    UWORD(165920160),
    UWORD(165920160),
    UWORD(165920160),
    UWORD(190578024),
    UWORD(190578024),
    UWORD(190578024),
    UWORD(190578024),
    UWORD(217887120),
    UWORD(217887120),
    UWORD(217887120),
    UWORD(217887120),
    UWORD(248031000),
    UWORD(248031000),
    UWORD(248031000),
    UWORD(248031000),
    UWORD(281199360),
    UWORD(281199360),
    UWORD(281199360),
    UWORD(281199360),
    UWORD(317588040),
    UWORD(317588040),
    UWORD(317588040),
    UWORD(317588040),
    UWORD(357399024),
    UWORD(357399024),
    UWORD(357399024),
    UWORD(357399024),
    UWORD(400840440),
    UWORD(400840440),
    UWORD(400840440),
    UWORD(400840440),
    UWORD(448126560),
    UWORD(448126560),
    UWORD(448126560),
    UWORD(448126560),
    UWORD(499477800),
    UWORD(499477800),
    UWORD(499477800),
    UWORD(499477800),
    UWORD(555120720),
    UWORD(555120720),
    UWORD(555120720),
    UWORD(555120720),
    UWORD(615288024),
    UWORD(615288024),
    UWORD(615288024),
    UWORD(615288024),
    UWORD(680218560),
    UWORD(680218560),
    UWORD(680218560),
    UWORD(680218560),
    UWORD(750157320),
    UWORD(750157320),
    UWORD(750157320),
    UWORD(750157320),
    UWORD(825355440),
    UWORD(825355440),
    UWORD(825355440),
    UWORD(825355440),
    UWORD(906070200),
    UWORD(906070200),
    UWORD(906070200),
    UWORD(906070200),
    UWORD(992565024),
    UWORD(992565024),
    UWORD(992565024),
    UWORD(992565024),
    UWORD(1085109480),
    UWORD(1085109480),
    UWORD(1085109480),
    UWORD(1085109480),
    UWORD(1183979280),
    UWORD(1183979280),
    UWORD(1183979280),
    UWORD(1183979280),
    UWORD(1289456280),
    UWORD(1289456280),
    UWORD(1289456280),
    UWORD(1289456280),
    UWORD(1401828480),
    UWORD(1401828480),
    UWORD(1401828480),
    UWORD(1401828480),
    UWORD(1521390024),
    UWORD(1521390024),
    UWORD(1521390024),
    UWORD(1521390024),
    UWORD(1648441200),
    UWORD(1648441200),
    UWORD(1648441200),
    UWORD(1648441200),
    UWORD(1783288440),
    UWORD(1783288440),
    UWORD(1783288440),
    UWORD(1783288440),
    UWORD(1926244320),
    UWORD(1926244320),
    UWORD(1926244320),
    UWORD(1926244320),
    UWORD(2077627560),
    UWORD(2077627560),
    UWORD(2077627560),
    UWORD(2077627560),
    UWORD(2237763024),
    UWORD(2237763024),
    UWORD(2237763024),
    UWORD(2237763024),
    UWORD(2406981720),
    UWORD(2406981720),
    UWORD(2406981720),
    UWORD(2406981720),
    UWORD(2585620800),
    UWORD(2585620800),
    UWORD(2585620800),
    UWORD(2585620800),
    UWORD(2774023560),
    UWORD(2774023560),
    UWORD(2774023560),
    UWORD(2774023560),
    UWORD(2972539440),
    UWORD(2972539440),
    UWORD(2972539440),
    UWORD(2972539440),
    UWORD(3181524024),
    UWORD(3181524024),
    UWORD(3181524024),
    UWORD(3181524024),
    UWORD(3401339040),
    UWORD(3401339040),
    UWORD(3401339040),
    UWORD(3401339040),
    UWORD(3632352360),
    UWORD(3632352360),
    UWORD(3632352360),
    UWORD(3632352360),
    UWORD(3874938000),
    UWORD(3874938000),
    UWORD(3874938000),
    UWORD(3874938000),
    UWORD(4129476120),
    UWORD(4129476120),
    UWORD(4129476120),
    UWORD(4129476120),
    UWORD(16974336),
    UWORD(16974336),
    UWORD(16974336),
    UWORD(17575740),
    UWORD(17575740),
    UWORD(17575740),
    UWORD(18191184),
    UWORD(18191184),
    UWORD(18191184),
    UWORD(18820830),
    UWORD(18820830),
    UWORD(18820830),
    UWORD(19464840),
    UWORD(19464840),
    UWORD(19464840),
    UWORD(20123376),
    UWORD(20123376),
    UWORD(20123376),
    UWORD(20796600),
    UWORD(20796600),
    UWORD(20796600),
    UWORD(21484674),
    UWORD(21484674),
    UWORD(21484674),
    UWORD(22187760),
    UWORD(22187760),
    UWORD(22187760),
    UWORD(22906020),
    UWORD(22906020),
    UWORD(22906020),
    UWORD(23639616),
    UWORD(23639616),
};

#endif

void _arb_exp_taylor_rs(nn_ptr y, ulong * error,
    nn_srcptr x, slong xn, ulong N)
{
    nn_ptr s, t, xpow;
    ulong new_denom, old_denom, c;
    slong power, k, m;

    TMP_INIT;
    TMP_START;

    if (N >= FACTORIAL_TAB_SIZE - 1)
    {
        flint_throw(FLINT_ERROR, "_arb_exp_taylor_rs: N too large!\n");
    }

    if (N <= 3)
    {
        if (N <= 1)
        {
            flint_mpn_zero(y, xn);
            y[xn] = N;
            error[0] = 0;
        }
        else if (N == 2)
        {
            flint_mpn_copyi(y, x, xn);
            y[xn] = 1;
            error[0] = 0;
        }
        else
        {
            /* 1 + x + x^2 / 2 */
            t = TMP_ALLOC_LIMBS(2 * xn);

            flint_mpn_sqr(t, x, xn);
            mpn_rshift(t + xn, t + xn, xn, 1);
            y[xn] = mpn_add_n(y, x, t + xn, xn) + 1;

            error[0] = 2;
        }
    }
    else
    {
        /* Choose m ~= sqrt(num_terms) (m must be even, >= 2) */
        /* TODO: drop evenness assumption since we don't have sign issues here? */
        /* TODO: then just need to fix power construction below... */
        m = 2;
        while (m * m < N)
            m += 2;

        /* todo: merge allocations */
        xpow = TMP_ALLOC_LIMBS((m + 1) * xn);
        s = TMP_ALLOC_LIMBS(xn + 2);
        t = TMP_ALLOC_LIMBS(2 * xn + 2);     /* todo: 1 limb too much? */

        /* higher index ---> */
        /*        | ---xn--- | */
        /* xpow = |  <temp>  | x^m | x^(m-1) | ... | x^2 | x | */

#define XPOW_WRITE(__k) (xpow + (m - (__k)) * xn)
#define XPOW_READ(__k) (xpow + (m - (__k) + 1) * xn)

        flint_mpn_copyi(XPOW_READ(1), x, xn);
        flint_mpn_sqr(XPOW_WRITE(2), XPOW_READ(1), xn);

        for (k = 4; k <= m; k += 2)
        {
            flint_mpn_mul_n(XPOW_WRITE(k - 1), XPOW_READ(k / 2), XPOW_READ(k / 2 - 1), xn);
            flint_mpn_sqr(XPOW_WRITE(k), XPOW_READ(k / 2), xn);
        }

        flint_mpn_zero(s, xn + 1);

        /* todo: skip one nonscalar multiplication (use x^m)
           when starting on x^0 */
        power = (N - 1) % m;

        for (k = N - 1; k >= 0; k--)
        {
            c = factorial_tab_numer[k];
            new_denom = factorial_tab_denom[k];
            old_denom = factorial_tab_denom[k+1];

            /* change denominators */
            if (new_denom != old_denom && (ulong) k < N - 1)
            {
                mpn_divrem_1(s, 0, s, xn + 1, old_denom);
            }

            if (power == 0)
            {
                /* add c * x^0 -- only top limb is affected */
                s[xn] += c;

                /* Outer polynomial evaluation: multiply by x^m */
                if (k != 0)
                {
                    flint_mpn_mul(t, s, xn + 1, XPOW_READ(m), xn);
                    flint_mpn_copyi(s, t + xn, xn + 1);
                }

                power = m - 1;
            }
            else
            {
                s[xn] += mpn_addmul_1(s, XPOW_READ(power), xn, c);

                power--;
            }
        }

        /* finally divide by denominator */
        mpn_divrem_1(y, 0, s, xn + 1, factorial_tab_denom[0]);

        /* error bound (ulp) */
        error[0] = 2;
    }

    TMP_END;
}
