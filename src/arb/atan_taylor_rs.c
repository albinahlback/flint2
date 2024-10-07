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

#define ODD_RECIPROCAL_TAB_SIZE 256

#if FLINT_BITS == 64

const ulong odd_reciprocal_tab_numer[ODD_RECIPROCAL_TAB_SIZE] = {
    UWORD(13835020108241056725), UWORD(4611673369413685575),
    UWORD(2767004021648211345), UWORD(1976431444034436675),
    UWORD(1537224456471228525), UWORD(1257729100749186975),
    UWORD(1064232316018542825), UWORD(922334673882737115),
    UWORD(813824712249473925), UWORD(728158953065318775),
    UWORD(658810481344812225), UWORD(601522613401785075),
    UWORD(553400804329642269), UWORD(512408152157076175),
    UWORD(477069658904864025), UWORD(446290971233582475),
    UWORD(419243033583062325), UWORD(395286288806887335),
    UWORD(373919462384893425), UWORD(354744105339514275),
    UWORD(337439514835147725), UWORD(321744653680024575),
    UWORD(307444891294245705), UWORD(294362129962575675),
    UWORD(43378025254434585), UWORD(41676926224848915),
    UWORD(40104212027684805), UWORD(38645877044859903),
    UWORD(37289881359075345), UWORD(36025817584191435),
    UWORD(34844643237168765), UWORD(33738464086782455),
    UWORD(32700357499496841), UWORD(31724227424884995),
    UWORD(30804684600975285), UWORD(29936947006581615),
    UWORD(18078521432946975), UWORD(17596427528068389),
    UWORD(17139377462404275), UWORD(16705469172216825),
    UWORD(16292988451915175), UWORD(15900386320543725),
    UWORD(15526259583589755), UWORD(15169334075921025),
    UWORD(14828450164102575), UWORD(14502550160495925),
    UWORD(14190667361345475), UWORD(34099971069969189),
    UWORD(33396878882959515), UWORD(32722194461081545),
    UWORD(32074230214327455), UWORD(31451429627641485),
    UWORD(30852354777591171), UWORD(30275675249038065),
    UWORD(29720158271991495), UWORD(29184659924748405),
    UWORD(28668117271213035), UWORD(70414222249896525),
    UWORD(69210560331094875), UWORD(68047357636454625),
    UWORD(66922607923455375), UWORD(65834435436895125),
    UWORD(64781084469904803), UWORD(63760909911323625),
    UWORD(62772368672388375), UWORD(61814011898764125),
    UWORD(60884477885248875), UWORD(59982485620282225),
    UWORD(22849011931010265), UWORD(22520249169412995),
    UWORD(22200813010981605), UWORD(21890312129709135),
    UWORD(21588376789989009), UWORD(21294657377880315),
    UWORD(21008823050660445), UWORD(20730560493698055),
    UWORD(20459572774826185), UWORD(11592603279646389),
    UWORD(11444926804746435), UWORD(11300965461290505),
    UWORD(11160580797175095), UWORD(11023641155491965),
    UWORD(10890021262698123), UWORD(10759601846378385),
    UWORD(10632269280149055), UWORD(10507915253480645),
    UWORD(3812050066792275), UWORD(3768483780314649),
    UWORD(3725902042683975), UWORD(3684271852262925),
    UWORD(3643561666050075), UWORD(3603741319973025),
    UWORD(3564781954351695), UWORD(3526655944144725),
    UWORD(3489336833624675), UWORD(56769492397408245),
    UWORD(56181207502098315), UWORD(55604989989256281),
    UWORD(55040472324390735), UWORD(54487301748266205),
    UWORD(53945139541815795), UWORD(53413660334507265),
    UWORD(52892551453194999), UWORD(52381512308719685),
    UWORD(7543627748528235), UWORD(7472124167973465),
    UWORD(7401963377663855), UWORD(7333107904383261),
    UWORD(7265521656416595), UWORD(7199169860467585),
    UWORD(7134019002001815), UWORD(7070036768800005),
    UWORD(827619730851221), UWORD(820327927055175),
    UWORD(813163491011025), UWORD(806123114465475),
    UWORD(799203602753325), UWORD(792401869963935),
    UWORD(785714934352425), UWORD(779139913981275),
    UWORD(1317621181161285), UWORD(1306776562386295),
    UWORD(1296108998611713), UWORD(1285614188906355),
    UWORD(1275287970521565), UWORD(1265126313385935),
    UWORD(1255125314861145), UWORD(1245281194744587),
    UWORD(30567046059275355), UWORD(30331007093566665),
    UWORD(30098585583271135), UWORD(29869699000888845),
    UWORD(29644267310316099), UWORD(29422212873534705),
    UWORD(29203460361463815), UWORD(28987936668759285),
    UWORD(438859621842675), UWORD(435667915502001),
    UWORD(432522298783575), UWORD(429421780512725),
    UWORD(426365397733275), UWORD(423352214710425),
    UWORD(420381321975615), UWORD(417451835411325),
    UWORD(22634811266652585), UWORD(22479245553479715),
    UWORD(22325803604309205), UWORD(22174442223941007),
    UWORD(22025119380682145), UWORD(21877794167433435),
    UWORD(21732426764327565), UWORD(21588978402846855),
    UWORD(19609694213279247), UWORD(19481943762378405),
    UWORD(19355847038997315), UWORD(19231372138424985),
    UWORD(19108487971406295), UWORD(18987164238254509),
    UWORD(18867371403943755), UWORD(18749080674138465),
    UWORD(9266890993958325), UWORD(9209510863964775),
    UWORD(9152836950955761), UWORD(9096856296821475),
    UWORD(9041556258542925), UWORD(8986924498672575),
    UWORD(8932948976158025), UWORD(8879617937494395),
    UWORD(552205768818165), UWORD(548947917674695),
    UWORD(545728281793905), UWORD(542546192687235),
    UWORD(539400997367309), UWORD(536292057901215),
    UWORD(533218750979145), UWORD(17071036886667995),
    UWORD(16974317130936165), UWORD(16878687175268919),
    UWORD(16784128703698785), UWORD(16690623808413555),
    UWORD(16598154978450045), UWORD(16506705088761615),
    UWORD(16416257389645113), UWORD(912010168967625),
    UWORD(907067024420375), UWORD(902177175232125),
    UWORD(897339764104875), UWORD(892553952029649),
    UWORD(887818917801375), UWORD(883133857549125),
    UWORD(29941527972993945), UWORD(29785175346503115),
    UWORD(29630447162884917), UWORD(29477318236978535),
    UWORD(29325763901569905), UWORD(29175759994144995),
    UWORD(29027282844047565), UWORD(28880309260027071),
    UWORD(1449018065980485), UWORD(1441754817529455),
    UWORD(1434564020434545), UWORD(1427444596015515),
    UWORD(1420395486899389), UWORD(1413415656496935),
    UWORD(1406504088494505), UWORD(592554335551395),
    UWORD(589684823030565), UWORD(586842968461743),
    UWORD(584028373888785), UWORD(581240648953755),
    UWORD(578479410716445), UWORD(575744283479015),
    UWORD(433241218467057), UWORD(431211985593675),
    UWORD(429201673306525), UWORD(427210018209975),
    UWORD(425236761774825), UWORD(423281650226435),
    UWORD(421344434435925), UWORD(2623079648743785),
    UWORD(2611183595915015), UWORD(2599394956655805),
    UWORD(2587712282693307), UWORD(2576134151674545),
    UWORD(2564659166589135), UWORD(2553285955207365),
    UWORD(210505107582315), UWORD(209579810406129),
    UWORD(208662612111135), UWORD(207753406829605),
    UWORD(206852090530995), UWORD(205958560982265),
    UWORD(205072717709223), UWORD(3779907202434825),
    UWORD(3763788195174975), UWORD(3747806079696525),
    UWORD(3731959119528675), UWORD(3716245607446449),
    UWORD(3700663864857575), UWORD(3685212241204725),
    UWORD(4501257379467765), UWORD(4482618632554855),
    UWORD(4464133607265969), UWORD(4445800409700195),
    UWORD(4427617176940685), UWORD(4409582076423615),
    UWORD(4391693305322505), UWORD(355589942551207),
    UWORD(354158997108345), UWORD(352739522170035),
    UWORD(351331380364965), UWORD(349934436506655),
    UWORD(348548557550193), UWORD(347173612549995),
    UWORD(6291002587483845), UWORD(6266380268159055),
};

const ulong odd_reciprocal_tab_denom[ODD_RECIPROCAL_TAB_SIZE] = {
    UWORD(13835020108241056725), UWORD(13835020108241056725),
    UWORD(13835020108241056725), UWORD(13835020108241056725),
    UWORD(13835020108241056725), UWORD(13835020108241056725),
    UWORD(13835020108241056725), UWORD(13835020108241056725),
    UWORD(13835020108241056725), UWORD(13835020108241056725),
    UWORD(13835020108241056725), UWORD(13835020108241056725),
    UWORD(13835020108241056725), UWORD(13835020108241056725),
    UWORD(13835020108241056725), UWORD(13835020108241056725),
    UWORD(13835020108241056725), UWORD(13835020108241056725),
    UWORD(13835020108241056725), UWORD(13835020108241056725),
    UWORD(13835020108241056725), UWORD(13835020108241056725),
    UWORD(13835020108241056725), UWORD(13835020108241056725),
    UWORD(2125523237467294665), UWORD(2125523237467294665),
    UWORD(2125523237467294665), UWORD(2125523237467294665),
    UWORD(2125523237467294665), UWORD(2125523237467294665),
    UWORD(2125523237467294665), UWORD(2125523237467294665),
    UWORD(2125523237467294665), UWORD(2125523237467294665),
    UWORD(2125523237467294665), UWORD(2125523237467294665),
    UWORD(1319732064605129175), UWORD(1319732064605129175),
    UWORD(1319732064605129175), UWORD(1319732064605129175),
    UWORD(1319732064605129175), UWORD(1319732064605129175),
    UWORD(1319732064605129175), UWORD(1319732064605129175),
    UWORD(1319732064605129175), UWORD(1319732064605129175),
    UWORD(1319732064605129175), UWORD(3239497251647072955),
    UWORD(3239497251647072955), UWORD(3239497251647072955),
    UWORD(3239497251647072955), UWORD(3239497251647072955),
    UWORD(3239497251647072955), UWORD(3239497251647072955),
    UWORD(3239497251647072955), UWORD(3239497251647072955),
    UWORD(3239497251647072955), UWORD(8097635558738100375),
    UWORD(8097635558738100375), UWORD(8097635558738100375),
    UWORD(8097635558738100375), UWORD(8097635558738100375),
    UWORD(8097635558738100375), UWORD(8097635558738100375),
    UWORD(8097635558738100375), UWORD(8097635558738100375),
    UWORD(8097635558738100375), UWORD(8097635558738100375),
    UWORD(3130314634548406305), UWORD(3130314634548406305),
    UWORD(3130314634548406305), UWORD(3130314634548406305),
    UWORD(3130314634548406305), UWORD(3130314634548406305),
    UWORD(3130314634548406305), UWORD(3130314634548406305),
    UWORD(3130314634548406305), UWORD(1796853508345190295),
    UWORD(1796853508345190295), UWORD(1796853508345190295),
    UWORD(1796853508345190295), UWORD(1796853508345190295),
    UWORD(1796853508345190295), UWORD(1796853508345190295),
    UWORD(1796853508345190295), UWORD(1796853508345190295),
    UWORD(659484661555063575), UWORD(659484661555063575),
    UWORD(659484661555063575), UWORD(659484661555063575),
    UWORD(659484661555063575), UWORD(659484661555063575),
    UWORD(659484661555063575), UWORD(659484661555063575),
    UWORD(659484661555063575), UWORD(10842973047904974795),
    UWORD(10842973047904974795), UWORD(10842973047904974795),
    UWORD(10842973047904974795), UWORD(10842973047904974795),
    UWORD(10842973047904974795), UWORD(10842973047904974795),
    UWORD(10842973047904974795), UWORD(10842973047904974795),
    UWORD(1576618199442401115), UWORD(1576618199442401115),
    UWORD(1576618199442401115), UWORD(1576618199442401115),
    UWORD(1576618199442401115), UWORD(1576618199442401115),
    UWORD(1576618199442401115), UWORD(1576618199442401115),
    UWORD(186214439441524725), UWORD(186214439441524725),
    UWORD(186214439441524725), UWORD(186214439441524725),
    UWORD(186214439441524725), UWORD(186214439441524725),
    UWORD(186214439441524725), UWORD(186214439441524725),
    UWORD(317546704659869685), UWORD(317546704659869685),
    UWORD(317546704659869685), UWORD(317546704659869685),
    UWORD(317546704659869685), UWORD(317546704659869685),
    UWORD(317546704659869685), UWORD(317546704659869685),
    UWORD(7855730837233766235), UWORD(7855730837233766235),
    UWORD(7855730837233766235), UWORD(7855730837233766235),
    UWORD(7855730837233766235), UWORD(7855730837233766235),
    UWORD(7855730837233766235), UWORD(7855730837233766235),
    UWORD(119808676763050275), UWORD(119808676763050275),
    UWORD(119808676763050275), UWORD(119808676763050275),
    UWORD(119808676763050275), UWORD(119808676763050275),
    UWORD(119808676763050275), UWORD(119808676763050275),
    UWORD(6541460456062597065), UWORD(6541460456062597065),
    UWORD(6541460456062597065), UWORD(6541460456062597065),
    UWORD(6541460456062597065), UWORD(6541460456062597065),
    UWORD(6541460456062597065), UWORD(6541460456062597065),
    UWORD(5980956735050170335), UWORD(5980956735050170335),
    UWORD(5980956735050170335), UWORD(5980956735050170335),
    UWORD(5980956735050170335), UWORD(5980956735050170335),
    UWORD(5980956735050170335), UWORD(5980956735050170335),
    UWORD(2974672009060622325), UWORD(2974672009060622325),
    UWORD(2974672009060622325), UWORD(2974672009060622325),
    UWORD(2974672009060622325), UWORD(2974672009060622325),
    UWORD(2974672009060622325), UWORD(2974672009060622325),
    UWORD(186093344091721605), UWORD(186093344091721605),
    UWORD(186093344091721605), UWORD(186093344091721605),
    UWORD(186093344091721605), UWORD(186093344091721605),
    UWORD(186093344091721605), UWORD(5991933947220466245),
    UWORD(5991933947220466245), UWORD(5991933947220466245),
    UWORD(5991933947220466245), UWORD(5991933947220466245),
    UWORD(5991933947220466245), UWORD(5991933947220466245),
    UWORD(5991933947220466245), UWORD(334707732011118375),
    UWORD(334707732011118375), UWORD(334707732011118375),
    UWORD(334707732011118375), UWORD(334707732011118375),
    UWORD(334707732011118375), UWORD(334707732011118375),
    UWORD(11407722157710693045), UWORD(11407722157710693045),
    UWORD(11407722157710693045), UWORD(11407722157710693045),
    UWORD(11407722157710693045), UWORD(11407722157710693045),
    UWORD(11407722157710693045), UWORD(11407722157710693045),
    UWORD(575260172194252545), UWORD(575260172194252545),
    UWORD(575260172194252545), UWORD(575260172194252545),
    UWORD(575260172194252545), UWORD(575260172194252545),
    UWORD(575260172194252545), UWORD(243539831911623345),
    UWORD(243539831911623345), UWORD(243539831911623345),
    UWORD(243539831911623345), UWORD(243539831911623345),
    UWORD(243539831911623345), UWORD(243539831911623345),
    UWORD(184127517848499225), UWORD(184127517848499225),
    UWORD(184127517848499225), UWORD(184127517848499225),
    UWORD(184127517848499225), UWORD(184127517848499225),
    UWORD(184127517848499225), UWORD(1151531965798521615),
    UWORD(1151531965798521615), UWORD(1151531965798521615),
    UWORD(1151531965798521615), UWORD(1151531965798521615),
    UWORD(1151531965798521615), UWORD(1151531965798521615),
    UWORD(95358813734788695), UWORD(95358813734788695),
    UWORD(95358813734788695), UWORD(95358813734788695),
    UWORD(95358813734788695), UWORD(95358813734788695),
    UWORD(95358813734788695), UWORD(1765216663537063275),
    UWORD(1765216663537063275), UWORD(1765216663537063275),
    UWORD(1765216663537063275), UWORD(1765216663537063275),
    UWORD(1765216663537063275), UWORD(1765216663537063275),
    UWORD(2165104799523994965), UWORD(2165104799523994965),
    UWORD(2165104799523994965), UWORD(2165104799523994965),
    UWORD(2165104799523994965), UWORD(2165104799523994965),
    UWORD(2165104799523994965), UWORD(176017021562847465),
    UWORD(176017021562847465), UWORD(176017021562847465),
    UWORD(176017021562847465), UWORD(176017021562847465),
    UWORD(176017021562847465), UWORD(176017021562847465),
    UWORD(3202120317029277105), UWORD(3202120317029277105),
};

#else

const ulong odd_reciprocal_tab_numer[ODD_RECIPROCAL_TAB_SIZE] = {
    UWORD(1673196525), UWORD(557732175),
    UWORD(334639305), UWORD(239028075),
    UWORD(185910725), UWORD(152108775),
    UWORD(128707425), UWORD(111546435),
    UWORD(98423325), UWORD(88062975),
    UWORD(79676025), UWORD(72747675),
    UWORD(66927861), UWORD(12806255),
    UWORD(11923065), UWORD(11153835),
    UWORD(10477845), UWORD(9879111),
    UWORD(9345105), UWORD(60902835),
    UWORD(57931965), UWORD(55237455),
    UWORD(52782457), UWORD(50536395),
    UWORD(48473685), UWORD(3267715),
    UWORD(3144405), UWORD(3030063),
    UWORD(2923745), UWORD(2824635),
    UWORD(6310395), UWORD(6110065),
    UWORD(5922063), UWORD(5745285),
    UWORD(5578755), UWORD(33304425),
    UWORD(32391975), UWORD(31528189),
    UWORD(30709275), UWORD(29931825),
    UWORD(18208955), UWORD(17770185),
    UWORD(17352063), UWORD(16953165),
    UWORD(16572195), UWORD(28280835),
    UWORD(27672645), UWORD(27090063),
    UWORD(26531505), UWORD(25995515),
    UWORD(1157205), UWORD(1134735),
    UWORD(1113121), UWORD(1092315),
    UWORD(1442445), UWORD(1416455),
    UWORD(1391385), UWORD(1367187),
    UWORD(590359), UWORD(580437),
    UWORD(570843), UWORD(561561),
    UWORD(2146173), UWORD(2112375),
    UWORD(2079625), UWORD(2047875),
    UWORD(2570805), UWORD(2532719),
    UWORD(2495745), UWORD(2459835),
    UWORD(1016015), UWORD(1001805),
    UWORD(987987), UWORD(974545),
    UWORD(3580965), UWORD(3533535),
    UWORD(3487345), UWORD(3442347),
    UWORD(4172637), UWORD(4120151),
    UWORD(4068969), UWORD(4019043),
    UWORD(1608711), UWORD(1589445),
    UWORD(1570635), UWORD(1552265),
    UWORD(5544525), UWORD(5481159),
    UWORD(5419225), UWORD(5358675),
    UWORD(6330885), UWORD(6261695),
    UWORD(6194001), UWORD(6127755),
    UWORD(2396095), UWORD(2371005),
    UWORD(2346435), UWORD(2322369),
    UWORD(8119797), UWORD(8038191),
    UWORD(7958209), UWORD(7879803),
    UWORD(9128493), UWORD(9040295),
    UWORD(8953785), UWORD(8868915),
    UWORD(3405815), UWORD(3374133),
    UWORD(3343035), UWORD(3312505),
    UWORD(11389725), UWORD(11287575),
    UWORD(11187241), UWORD(11088675),
    UWORD(12648405), UWORD(12538895),
    UWORD(12431265), UWORD(12325467),
    UWORD(4665519), UWORD(4626477),
    UWORD(4588083), UWORD(4550321),
    UWORD(15437253), UWORD(15312255),
    UWORD(15189265), UWORD(15068235),
    UWORD(16973565), UWORD(16840439),
    UWORD(16709385), UWORD(16580355),
    UWORD(6202855), UWORD(6155685),
    UWORD(6109227), UWORD(6063465),
    UWORD(73983), UWORD(73437),
    UWORD(72899), UWORD(77283),
    UWORD(76725), UWORD(76175),
    UWORD(80655), UWORD(80085),
    UWORD(79523), UWORD(84099),
    UWORD(83517), UWORD(82943),
    UWORD(87615), UWORD(87021),
    UWORD(86435), UWORD(91203),
    UWORD(90597), UWORD(89999),
    UWORD(94863), UWORD(94245),
    UWORD(93635), UWORD(98595),
    UWORD(97965), UWORD(97343),
    UWORD(102399), UWORD(101757),
    UWORD(101123), UWORD(106275),
    UWORD(105621), UWORD(104975),
    UWORD(110223), UWORD(109557),
    UWORD(108899), UWORD(114243),
    UWORD(113565), UWORD(112895),
    UWORD(118335), UWORD(117645),
    UWORD(116963), UWORD(122499),
    UWORD(121797), UWORD(121103),
    UWORD(126735), UWORD(126021),
    UWORD(125315), UWORD(131043),
    UWORD(130317), UWORD(129599),
    UWORD(135423), UWORD(134685),
    UWORD(133955), UWORD(139875),
    UWORD(139125), UWORD(138383),
    UWORD(144399), UWORD(143637),
    UWORD(142883), UWORD(148995),
    UWORD(148221), UWORD(147455),
    UWORD(153663), UWORD(152877),
    UWORD(152099), UWORD(158403),
    UWORD(157605), UWORD(156815),
    UWORD(163215), UWORD(162405),
    UWORD(161603), UWORD(168099),
    UWORD(167277), UWORD(166463),
    UWORD(173055), UWORD(172221),
    UWORD(171395), UWORD(178083),
    UWORD(177237), UWORD(176399),
    UWORD(183183), UWORD(182325),
    UWORD(181475), UWORD(188355),
    UWORD(187485), UWORD(186623),
    UWORD(193599), UWORD(192717),
    UWORD(191843), UWORD(198915),
    UWORD(198021), UWORD(197135),
    UWORD(204303), UWORD(203397),
    UWORD(202499), UWORD(209763),
    UWORD(208845), UWORD(207935),
    UWORD(215295), UWORD(214365),
    UWORD(213443), UWORD(220899),
    UWORD(219957), UWORD(219023),
    UWORD(226575), UWORD(225621),
    UWORD(224675), UWORD(232323),
    UWORD(231357), UWORD(230399),
    UWORD(238143), UWORD(237165),
    UWORD(236195), UWORD(244035),
    UWORD(243045), UWORD(242063),
    UWORD(249999), UWORD(248997),
    UWORD(248003), UWORD(256035),
    UWORD(255021), UWORD(254015),
    UWORD(262143), UWORD(261117),
};

const ulong odd_reciprocal_tab_denom[ODD_RECIPROCAL_TAB_SIZE] = {
    UWORD(1673196525), UWORD(1673196525),
    UWORD(1673196525), UWORD(1673196525),
    UWORD(1673196525), UWORD(1673196525),
    UWORD(1673196525), UWORD(1673196525),
    UWORD(1673196525), UWORD(1673196525),
    UWORD(1673196525), UWORD(1673196525),
    UWORD(1673196525), UWORD(345768885),
    UWORD(345768885), UWORD(345768885),
    UWORD(345768885), UWORD(345768885),
    UWORD(345768885), UWORD(2375210565),
    UWORD(2375210565), UWORD(2375210565),
    UWORD(2375210565), UWORD(2375210565),
    UWORD(2375210565), UWORD(166653465),
    UWORD(166653465), UWORD(166653465),
    UWORD(166653465), UWORD(166653465),
    UWORD(384934095), UWORD(384934095),
    UWORD(384934095), UWORD(384934095),
    UWORD(384934095), UWORD(2364614175),
    UWORD(2364614175), UWORD(2364614175),
    UWORD(2364614175), UWORD(2364614175),
    UWORD(1474925355), UWORD(1474925355),
    UWORD(1474925355), UWORD(1474925355),
    UWORD(1474925355), UWORD(2573555985),
    UWORD(2573555985), UWORD(2573555985),
    UWORD(2573555985), UWORD(2573555985),
    UWORD(116877705), UWORD(116877705),
    UWORD(116877705), UWORD(116877705),
    UWORD(157226505), UWORD(157226505),
    UWORD(157226505), UWORD(157226505),
    UWORD(69072003), UWORD(69072003),
    UWORD(69072003), UWORD(69072003),
    UWORD(268271625), UWORD(268271625),
    UWORD(268271625), UWORD(268271625),
    UWORD(341917065), UWORD(341917065),
    UWORD(341917065), UWORD(341917065),
    UWORD(143258115), UWORD(143258115),
    UWORD(143258115), UWORD(143258115),
    UWORD(533563785), UWORD(533563785),
    UWORD(533563785), UWORD(533563785),
    UWORD(655104009), UWORD(655104009),
    UWORD(655104009), UWORD(655104009),
    UWORD(265437315), UWORD(265437315),
    UWORD(265437315), UWORD(265437315),
    UWORD(959202825), UWORD(959202825),
    UWORD(959202825), UWORD(959202825),
    UWORD(1145890185), UWORD(1145890185),
    UWORD(1145890185), UWORD(1145890185),
    UWORD(452861955), UWORD(452861955),
    UWORD(452861955), UWORD(452861955),
    UWORD(1599600009), UWORD(1599600009),
    UWORD(1599600009), UWORD(1599600009),
    UWORD(1871341065), UWORD(1871341065),
    UWORD(1871341065), UWORD(1871341065),
    UWORD(725438595), UWORD(725438595),
    UWORD(725438595), UWORD(725438595),
    UWORD(2517129225), UWORD(2517129225),
    UWORD(2517129225), UWORD(2517129225),
    UWORD(2896484745), UWORD(2896484745),
    UWORD(2896484745), UWORD(2896484745),
    UWORD(1105728003), UWORD(1105728003),
    UWORD(1105728003), UWORD(1105728003),
    UWORD(3782126985), UWORD(3782126985),
    UWORD(3782126985), UWORD(3782126985),
    UWORD(4294311945), UWORD(4294311945),
    UWORD(4294311945), UWORD(4294311945),
    UWORD(1618945155), UWORD(1618945155),
    UWORD(1618945155), UWORD(1618945155),
    UWORD(19901427), UWORD(19901427),
    UWORD(19901427), UWORD(21252825),
    UWORD(21252825), UWORD(21252825),
    UWORD(22664055), UWORD(22664055),
    UWORD(22664055), UWORD(24136413),
    UWORD(24136413), UWORD(24136413),
    UWORD(25671195), UWORD(25671195),
    UWORD(25671195), UWORD(27269697),
    UWORD(27269697), UWORD(27269697),
    UWORD(28933215), UWORD(28933215),
    UWORD(28933215), UWORD(30663045),
    UWORD(30663045), UWORD(30663045),
    UWORD(32460483), UWORD(32460483),
    UWORD(32460483), UWORD(34326825),
    UWORD(34326825), UWORD(34326825),
    UWORD(36263367), UWORD(36263367),
    UWORD(36263367), UWORD(38271405),
    UWORD(38271405), UWORD(38271405),
    UWORD(40352235), UWORD(40352235),
    UWORD(40352235), UWORD(42507153),
    UWORD(42507153), UWORD(42507153),
    UWORD(44737455), UWORD(44737455),
    UWORD(44737455), UWORD(47044437),
    UWORD(47044437), UWORD(47044437),
    UWORD(49429395), UWORD(49429395),
    UWORD(49429395), UWORD(51893625),
    UWORD(51893625), UWORD(51893625),
    UWORD(54438423), UWORD(54438423),
    UWORD(54438423), UWORD(57065085),
    UWORD(57065085), UWORD(57065085),
    UWORD(59774907), UWORD(59774907),
    UWORD(59774907), UWORD(62569185),
    UWORD(62569185), UWORD(62569185),
    UWORD(65449215), UWORD(65449215),
    UWORD(65449215), UWORD(68416293),
    UWORD(68416293), UWORD(68416293),
    UWORD(71471715), UWORD(71471715),
    UWORD(71471715), UWORD(74616777),
    UWORD(74616777), UWORD(74616777),
    UWORD(77852775), UWORD(77852775),
    UWORD(77852775), UWORD(81181005),
    UWORD(81181005), UWORD(81181005),
    UWORD(84602763), UWORD(84602763),
    UWORD(84602763), UWORD(88119345),
    UWORD(88119345), UWORD(88119345),
    UWORD(91732047), UWORD(91732047),
    UWORD(91732047), UWORD(95442165),
    UWORD(95442165), UWORD(95442165),
    UWORD(99250995), UWORD(99250995),
    UWORD(99250995), UWORD(103159833),
    UWORD(103159833), UWORD(103159833),
    UWORD(107169975), UWORD(107169975),
    UWORD(107169975), UWORD(111282717),
    UWORD(111282717), UWORD(111282717),
    UWORD(115499355), UWORD(115499355),
    UWORD(115499355), UWORD(119821185),
    UWORD(119821185), UWORD(119821185),
    UWORD(124249503), UWORD(124249503),
    UWORD(124249503), UWORD(128785605),
    UWORD(128785605), UWORD(128785605),
    UWORD(133430787), UWORD(133430787),
};

#endif

void _arb_atan_taylor_rs(nn_ptr y, ulong * error,
    nn_srcptr x, slong xn, ulong N, int alternating)
{
    nn_ptr s, t, xpow;
    ulong new_denom, old_denom, c;
    slong power, k, m;

    TMP_INIT;
    TMP_START;

    if (N >= ODD_RECIPROCAL_TAB_SIZE)
    {
        flint_throw(FLINT_ERROR, "_arb_atan_taylor_rs: N too large!\n");
    }

    if (N <= 2)
    {
        if (N == 0)
        {
            flint_mpn_zero(y, xn);
            error[0] = 0;
        }
        else if (N == 1)
        {
            flint_mpn_copyi(y, x, xn);
            error[0] = 0;
        }
        else
        {
            t = TMP_ALLOC_LIMBS(3 * xn);

            /* x * (1 - x^2 / 3) */

            /* higher index ---> */
            /* t = |          | x^2 (lo) | x^2 (hi) | */
            flint_mpn_sqr(t + xn, x, xn);

            /* t = | x^3 (lo) | x^3 (hi) | x^2 (hi) | */
            flint_mpn_mul_n(t, t + 2 * xn, x, xn);

            /* y = x - x^3 / 3 */
            mpn_divrem_1(t, 0, t + xn, xn, 3);

            if (alternating)
                mpn_sub_n(y, x, t, xn);
            else
                mpn_add_n(y, x, t, xn);

            error[0] = 3;
        }
    }
    else
    {
        /* Choose m ~= sqrt(num_terms) (m must be even, >= 2) */
        m = 2;
        while (m * m < N)
            m += 2;

        /* todo: merge allocations */
        xpow = TMP_ALLOC_LIMBS((m + 1) * xn);
        s = TMP_ALLOC_LIMBS(xn + 2);
        t = TMP_ALLOC_LIMBS(2 * xn + 2);     /* todo: 1 limb too much? */

        /* higher index ---> */
        /*        | ---xn--- | */
        /* xpow = |  <temp>  | (x^2)^m | (x^2)^(m-1) | ... | (x^2)^2 | x^2 | */

#define XPOW_WRITE(__k) (xpow + (m - (__k)) * xn)
#define XPOW_READ(__k) (xpow + (m - (__k) + 1) * xn)

        flint_mpn_sqr(XPOW_WRITE(1), x, xn);
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
            c = odd_reciprocal_tab_numer[k];
            new_denom = odd_reciprocal_tab_denom[k];
            old_denom = odd_reciprocal_tab_denom[k+1];

            /* change denominators */
            if (new_denom != old_denom && (ulong) k < N - 1)
            {
                /* hack when s is negative: add 1 to get a positive number */
                if (alternating && (k % 2 == 0))
                    s[xn] += old_denom;

                /* multiply by new denominator */
                s[xn + 1] = mpn_mul_1(s, s, xn + 1, new_denom);
                /* divide by old denominator */
                mpn_divrem_1(s, 0, s, xn + 2, old_denom);

                if (s[xn + 1] != 0)
                {
                    flint_throw(FLINT_ERROR, "bad division!\n");
                }

                /* subtract 1 */
                if (alternating && (k % 2 == 0))
                    s[xn] -= new_denom;
            }

            if (power == 0)
            {
                /* sub/add c * x^0 -- only top limb is affected */
                if (alternating & k)
                    s[xn] -= c;
                else
                    s[xn] += c;

                /* Outer polynomial evaluation: multiply by (x^2)^m */
                if (k != 0)
                {
                    flint_mpn_mul(t, s, xn + 1, XPOW_READ(m), xn);
                    flint_mpn_copyi(s, t + xn, xn + 1);
                }

                power = m - 1;
            }
            else
            {
                if (alternating & k)
                    s[xn] -= mpn_submul_1(s, XPOW_READ(power), xn, c);
                else
                    s[xn] += mpn_addmul_1(s, XPOW_READ(power), xn, c);

                power--;
            }
        }

        /* finally divide by denominator and multiply by x */
        mpn_divrem_1(s, 0, s, xn + 1, odd_reciprocal_tab_denom[0]);
        flint_mpn_mul(t, s, xn + 1, x, xn);
        flint_mpn_copyi(y, t + xn, xn);

        /* error bound (ulp) */
        error[0] = 2;
    }

    TMP_END;
}
