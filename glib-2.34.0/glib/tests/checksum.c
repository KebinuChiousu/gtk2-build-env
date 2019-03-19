#include "config.h"

#include <glib.h>
#include <string.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <stdlib.h>

/* Test GChecksum by computing the checksums of every initial
 * substring of this string, calling g_checksum_update with chunks of
 * every possible size. That is, first it computes the checksums of
 * "", then "T". Then it computes the checksums of "Th", first by
 * feeding the GChecksum 1 letter a time, then 2. Then it does "The",
 * first feeding it one letter at a time, then 2, then 3. Etc.
 *
 * MD5, SHA1, and SHA256 all use a 64-byte buffer internally; this
 * string is intentionally more than twice that length.
 */

#define FIXED_STR               "The quick brown fox jumps over the lazy dog. Jackdaws love my big sphinx of quartz. Pack my box with five dozen liquor jugs. How razorback-jumping frogs can level six piqued gymnasts!"
#define FIXED_LEN               (strlen (FIXED_STR))

const char *MD5_sums[] = {
  "d41d8cd98f00b204e9800998ecf8427e",
  "b9ece18c950afbfa6b0fdbfa4ff731d3",
  "eeeb9a8eb45dd351d9ec0eb4acce66ce",
  "a4704fd35f0308287f2937ba3eccf5fe",
  "02edd93949f6d3c57d9822691b59f649",
  "6131a51747610d0ae4e86c3a3416788c",
  "8c871099d54c09d4099fa7a0e77c9113",
  "bbb9873bad399cd1cc0d5e336ca5beee",
  "b9b926544b8ecd5c3ef553a87170b726",
  "912d57cea222bc1730dd531b9d6afbb6",
  "03c729679ca3252a4735c4148b7c11e3",
  "d7027ce01f22eb9d2bb32d9a153a7e29",
  "e05e6a516c92259691cf9194dfdeff92",
  "dd1ac3c70b6f51dd545cdf64053209d4",
  "caa1e1e79c65480a48cf08a38ac1d87d",
  "5aa207e85988921b8733912c4f526c80",
  "b0e45b65d9e1d88169c40dc47605e2d9",
  "e4b6d6fabe9dfcbe83a51d19df5f0ac3",
  "168534eca593b6cef86aea9081f0f5bf",
  "a2004f37730b9445670a738fa0fc9ee5",
  "c4314972a672ded8759cafdca9af3238",
  "29dcbbf4add427ccba06d3c37ad44aa9",
  "d0312d0e9e2d8c063d95a06fbbba9cb1",
  "770fd972e360cb8538ce6a880741936e",
  "8e53cb84ef3d981a86fbb69b24827c46",
  "83de97cab1f553eb3acc22866a4f6942",
  "a2829f93d701f36d808d0a698dcebf02",
  "efcead92aba26426db84b75413f17c10",
  "60a0732774106c2348eb576596668eb9",
  "d44f138aa2f39488c03391771eea258c",
  "f85199fa76594dfb190fab5dfe42a769",
  "cd4c02f190df2372cb703994dd84e881",
  "566cb723d4fb7a7dd38163532fe760b7",
  "4433001bd59da157c18b09f6c10d4163",
  "b76b517e01f5b708af50af906adb2dac",
  "0f611396bcfe9ab7666c45ebd37e59ba",
  "4c6606c2117565959048d356c1d7f6cc",
  "5f7f3f510b8a8f0a5e1d6193c6c7f3af",
  "542560ce828579cfe777aa165b4d1bed",
  "171e092149d366acca00d1cd783e61cd",
  "4ed8b5a69f7c329f498320947db666f2",
  "eb4c251a5abb3c59d306276ba2dc644d",
  "2b6e07526e77047d7935681efc3b9f90",
  "9e107d9d372bb6826bd81d3542a419d6",
  "e4d909c290d0fb1ca068ffaddf22cbd0",
  "1c6d98786bea70b9c34ce7f33201120c",
  "bdda04a65a37f97d3ac3be6b0d5f58ea",
  "954c69b280f0b5eed4b36eb714d26f82",
  "e5fad54e00d29bf5b1671b3d351624e9",
  "1a0b3d4eec1bd869af85945f60ff19c3",
  "055031167bd9f17448623653eb4b27ed",
  "4ca7c851615ea3abc43b5e1df410b84a",
  "774873408e0032f8c56106dc28d489e2",
  "fc44cc8ad9ff4aef8a4187688cb65378",
  "b939f1b04b296ac8ff8261876ae86704",
  "de9362af59e6e23688a243f909e9fdbd",
  "6827a93d7492d3da381d7b45f2a0b94f",
  "459ade91c05ca5f8bfdc8c3f6014ce04",
  "55b143ec7d943b04666010e165d753e0",
  "04ad29c207b52f46fd50f208744d936d",
  "8d26f6529919e3d3e33b5e147e96bd8c",
  "de98a267f5acd95c52bf439be075f360",
  "4a8a2b0f0cc485c957992c6c9865b33d",
  "566f00c9d7ac74a1daeb2925de2aca23",
  "6ebee39c52840729c65d815fbdb9e9c7",
  "7dc322a68ec5881e78cb718a3ca9a557",
  "b00112c2c7844e0c6c0cab1fdc7a12ab",
  "6f78ec779e96448daa9675bf06a0dbe3",
  "8bba94005e06aefd071ed8a5c1b89068",
  "220316718ce3875281be580a731ef0a1",
  "7dd175908a4fce0e510287a9f884ef1d",
  "030d864e63a6b67e11084f27ac5a422f",
  "cad084c9d6c71aa60c414b3df22e4ef2",
  "a10296630814335017df32f94b5202ff",
  "de23bdf63d07cc75716e1e303df0677c",
  "9718898182f2ba3a4428d9e357f5788e",
  "9dfc12c4b82dcf727fc6599a0696a48c",
  "6cca243870d308ffe8ae51993258e9ef",
  "6b425096ac7743989c9744ff45ea027f",
  "742a87784ffd6e2b0697aabf6b453309",
  "b9b7f74d898d1fe768777bd7fb7844e7",
  "4717614d82c1df37d608111953c75912",
  "43298b7db8498f89b9aa1bcb410a8ed2",
  "1b3621f615f0861d672d406257f5a97b",
  "9ef3e55a2eb9d5d41f9f850cc86f8fea",
  "3ec2cbcec99a048d9410c64a61796b0f",
  "e75f9f48ac684c1c49a256df39ac118b",
  "3518518b7b3b87f298d0518ccab65534",
  "d936105bf33a89e00fe8ed8711b732d3",
  "70858151e61f8862decb044c2050ae40",
  "81491684aa39d20b064ceff099a3175b",
  "bd73078b5a0a3a6d40fb1376347d64a6",
  "9da1f6dc1bc2ffb5ccafa14a04ff5f84",
  "a5c9c51a8981234ef59a969e3ad147ef",
  "c105573b4d5ef469c7867094b4e589e1",
  "d479c97efb06a112534196e257192c4a",
  "fc7b07eb35cc515c1beb93aaa4e51a64",
  "83470666e83e382a35d97f406f79eb70",
  "e2ecf716fa93c1e1764a8e584cbffe04",
  "534a7c131ee92bd5c9105cd293a9fa6e",
  "5afea20e81c95d55e70bb0805158d207",
  "8bb0ebc08bd51a0f62808c76005d5d33",
  "c689312f4c99858ba414b63b61408f7b",
  "cf1636f7d96fae80a428db4dbd93450d",
  "963b816a27e6432c8200f35c11cb3d18",
  "2dcd8661e650a8efe99642df35e1c0a4",
  "2f6207c7ae99db3da286ebdb98b10f60",
  "b515b746e01836e24966ff679f9dde6b",
  "5b53b6ca7982077b891b03ae9546984d",
  "4c57e9d52f8e782b44304f2d4613456d",
  "7f28eb1a0f03dd38c73da46973299d00",
  "997d1c07005040126addd2dbecc623fc",
  "817dbe3e415b05eca731e27ca792adbc",
  "ebffcb6fd54cfc146afe9485884b540e",
  "2d6394332758bd5411eada08d85af3d6",
  "27e0d08eda3a775290e0962483fa5ec8",
  "d444cd632037609ccb972ce79009b16e",
  "31c0453b13e1dd83f6ea55b7be54da15",
  "aa95999a313b3794d7902a751ee77c05",
  "cd30f6386d09f62f49537b2d23ea713e",
  "149a308e31876049d76b7393512451d6",
  "d0d4a7c2254d9f8c18668c103a3d7f82",
  "1f822faa98bc97d382fb28019730daf3",
  "a59e31843f29f63c8ec857084fd91161",
  "e871798ecb332a9a082ab69d747c624d",
  "dba105cfd9294cbc4269096d9c682b89",
  "c9cbdc59fb3afff3051b33788d1e946a",
  "890247b165402b325ac88212b21e4e42",
  "777c5b13c598663f136be27451b5379a",
  "888e851163704b4fed2d9b82e51aff16",
  "3069f2cddd3a17dd655c61372def9c0d",
  "39ae3b6ae2e9ecf5f0c25eff8d52ddef",
  "058dcd07dc12be85774e7f72587bfe43",
  "522c5460f239de773cdbcefb4d55b129",
  "c6b5babfeaae6d7bb86c1c2b64fa1b56",
  "fffa674d8c9bcb251c0ab3cf9d7aec89",
  "7aabad234a1f9f05ef6c5fb6ddc15b0a",
  "9b3ca93cfa10b081de65516d67170e3b",
  "1990bf44ba11b087af262e017d8c823e",
  "072e4bc6ef0ee5d9e7c56dafb9f65088",
  "e2825a9231a65676a7b79b648fd94fcb",
  "ab864a28e6eac29000429a5536fd9cf9",
  "decfbab07f8d11187365c385f12d038b",
  "1f0dd358531e06187d33964d0e0e115f",
  "acdf4cc64f0c62013621d6ebc69687d2",
  "6827965643e24616e892e5636f1265c9",
  "2daed5786790d38ede194d351b383d46",
  "eb05cb49a9e01e2c0a1329c2d1859394",
  "83065746806dbca73e787939d359e74c",
  "0a318bc9d7e2d4d03a96e755fd2214f6",
  "85421302d14c37029512ab3e848c4498",
  "02ee794a181044b80588bd14f76ea4dd",
  "abeca493fed89cd65ed112e069a695c1",
  "e5828e0a11268c9baaaac24bd46d1e15",
  "e0a8b89702312967460ad9940aa108d5",
  "6e5c8f2aacd19e70d15be253369cdfc4",
  "eabc6ce71e74b5b48150ceda5a916948",
  "5c263ad8e8dc1fd66e9b35daf7f74c48",
  "030b2b56e20c53b75191369104b9509a",
  "1225f4418731a8e7944d1366efd89234",
  "9085ba0fe1c64c3dce45708de32c3440",
  "49efb746a4938e7da19ecb3bb2c8e1d3",
  "833095be66f1f7b5942a817846c97ed5",
  "28f9f64eba29e57a7bd4bc0840aedf90",
  "9b5984b93bd951a70dea62942634c009",
  "ddb73667065d5ab761612be590e339e5",
  "59c4b46e73c2679610b7a4e9b3a04bc1",
  "fcc2a983de8f0ebb193864e0c60a00a6",
  "af8f1f4bb88555d688508eb9f3c876ac",
  "814e087171d6a45ac4fb4a110e889a38",
  "733130f693a1c3a24703052717330807",
  "b319f375927ed3f197a26c1112df86ae",
  "ace1c7e7c2ffcfe31a042d2b9ae00905",
  "5231c151c22b31180e900647fd5097ed",
  "07e7238f4f3d8b3a279a2d9f78fa8b08",
  "208b1f437aac92a96eef5ec9ca5d53da",
  "3a675752c5faa15bd61c63499684c570",
  "efa1debf8fb84e142c83c0dcf221d247",
  "d940ea701a781a4ff62a99d831c2286a",
  "d88294e690a6375d22b12fcc88bebb56",
  "f209ebcae30e147ccd9e42d32cfe33b4",
  "fbf1e18620fe5a9c40a65cbbd50af177",
  "4e682a50db552d15bfe109a1147f6770",
  "407b72260377f77f8e63e13dc09bda2c"
};

const char *SHA1_sums[] = {
  "da39a3ee5e6b4b0d3255bfef95601890afd80709",
  "c2c53d66948214258a26ca9ca845d7ac0c17f8e7",
  "6929e765f6bd128088cdf81ba4805d3a84da4e5e",
  "93ef0dd827103681fcee453b78be2ff14e1a261d",
  "9f7ed32a201bab6d11f7be88b9335973d93de3f5",
  "a2b847dd0e90bca83b418103baa63c67c85b5a30",
  "ee4801c9d009963ac6dda49b100f0d9a9f3983b2",
  "0dab89aa7606af6df94d1c3f8872ca98440ce299",
  "2eb3456b1b4fb96df1309eff21b02814663f939a",
  "30b59bc6c7c1622283a23950f2984bc5cd4fdd51",
  "4d39faadbf264f3fb59268228994276c36fc3172",
  "8312b76dd9300bcbbd9c5148461949f31f593bdc",
  "0d12bfd71a11c686cf53adaacf0bec05c557e768",
  "ca150c0c3372de80daa720b7d4081022b7befbe4",
  "d2ac2275af550efdde0aca4713835f3480498387",
  "07bb8c8ec36e16d57141fbf95fb8478a668b451f",
  "6ad802395de4400a9892c9f65868879bee5d1bf6",
  "569c7018c812f0cc51c093dbc026baebaab1eb22",
  "b8cfd76b506e7aaeb55c3d4e73e8868df8c4dfb1",
  "c519c1a06cdbeb2bc499e22137fb48683858b345",
  "3e3436a073e72c5300cdca6ce5c321e49dfc412e",
  "e2b72fb64787db45dc11bca1f194bef40b5be347",
  "52f4aaab2d5f9bc918700c517253e5bd6981ba95",
  "001233b5471e0bfa33f8133cf3cc3b97351033a5",
  "b2cc1f24e2599121adf86c5161dfe43fd5486985",
  "743e27565bb39d4cf6cdf7b19450f94ef12b2206",
  "6b57e81439c46aca165e5eacd44c0829670c9bb5",
  "4bbe681b61206e8689fce488662e7be67053ad03",
  "332ffb34a55ebf0b01beb604bca729887fd4c047",
  "b09b432ae19ca6971bb28a3705c9be3b02ec388f",
  "051605798e587fd98b428b88077d015494978bda",
  "33d579648c883c1b3a2ba91b7d4efd79d2d04e65",
  "d035de80a23137cd473991fea53b6b1b1f22e57d",
  "4ed82184201c1063c9f89d83b01d277e2db0847c",
  "1477d62ad76e1d543380ce2f4253a701fe039af2",
  "df72568859f54940e93ba5ace28430d38e4ab10f",
  "65ebceacd76a51d7076728d8ecbfcb1a4014fe3d",
  "0f5f0f1c642e616224d356a835ed3d054935608a",
  "caa9daf50b65b3739eb9a88547c516d89b72ac11",
  "1e9c81970164a681a35993d773e1d55d328ed64b",
  "8aefdcfcbaa21522fb39162d7507492e47b30f25",
  "a374c23022eea446300e1b3303272bdb8f6cfab3",
  "f2f38c31109f8a9421f301e9d554193bc4274a32",
  "2fd4e1c67a2d28fced849ee1bb76e7391b93eb12",
  "408d94384216f890ff7a0c3528e8bed1e0b01621",
  "22b759d30862cc7c7eb3ce9616a9d4e853b1e14d",
  "97e2821bba8dbd62f7823b7ecf095dad5d152371",
  "190c9e3674d72f3abfa027a38a425de21ea124a5",
  "8a9f1acbeb7dea1bdb61c0e5885043caa84c3812",
  "8431fa593176872aea33d2ece77fff42f22c409b",
  "08efef7adec17bd8d97f24cc373bfeab4b602d7a",
  "669f7e46d635f02a355635d9a09bf3bf2936bcf8",
  "695ed476d76f489707db6862a6411973d0207558",
  "084ef870fa0d4674d8488040a3d147235cfcb50d",
  "2a7d533528fcdaa6795ece88ab526b3e077f4f52",
  "4546fb23d600a7e358edf7033eef05af19b4fb1f",
  "59c3623fbc8c29341481a7fead82ef6b3aa43d93",
  "806b2e0c9be4502325b23d20f085b6d8dd8f559b",
  "113382ddaeee3a9880b3328b4240ae9e750be3cd",
  "543bef2867245f702b77470bfe08350cff1090ab",
  "977eb8d9219bae5415e13656113e30d66c2f5b45",
  "58153daaa0ec2e5f3e96879a33aee162f0c1283c",
  "6663fde567230f1d0247dc7ea3144b3aedac160e",
  "b418a310c03a4795b9ed4577c876b9dc50c18481",
  "75c2add8fd09dedee1f2728426f5e94f9860d062",
  "3f188f1a66fd317b645ea7eecebcae844bba9944",
  "049296261ba622294ec83fbe8f5cb0d2cc3c475e",
  "c60fe6fe0ea55fb34b3b5e740400c495e305597b",
  "64df347932a61deb5ed0e41e811d24cdf745c7a8",
  "eaaf91d87507541a572b693cd53cb31a4ff3ac2b",
  "712424206790276862399340047ca6d6028ab2e0",
  "2cc40cd0dd42274998746980844a8df708a3af94",
  "da0ba0bed525b2a41d906aaf078f7da4c53bfad4",
  "ee16dc82f66d8f069d83b76f1c433d658367dd27",
  "64fe9ccff8f5235dd72a85e6c7676bc091f34038",
  "20e9001f77c5454f9b9a9fa681f40067e4e1b8c2",
  "40cce478fceb688eea9d9385f00acfc73ecb2f9d",
  "21955259821de3bf9de7c8708d7a4d037d244c92",
  "b922eb3c6a86c38717535220cbafffe3032803a3",
  "be386c5615669fb19a05101d90df850569a366a1",
  "c733de72b09be501a6d8555a51bab2ca9d65b203",
  "740eaaab9d5ac5a9854260b09a1127c520b7b27c",
  "0b3e8e2cf27e492dfb0bfbe9b8d6a3b2e2bc17f9",
  "2516ba614aced5f991fc2f67e66fa90f3dec756f",
  "5abe738e94964292a2bd38e6cf048138bb593fe4",
  "1c5d0b73e977edfe89b447bfca585e8826b5783a",
  "e3096837858dc2247961a29fb59164d5e39d8cd1",
  "9a6d5ce05968464a6c00426a5d18595e5e0c2534",
  "e74f03f5e56d5a9926c6f6351fd8131242a84ef1",
  "573b84daad0e7149c3b128f65d75120095a1d3c5",
  "5facae19039c0444d188729f5eeaa58440b55d7a",
  "e617e14b9abc583b5e31b9ee315217cf52e7053f",
  "62bbd3fc168a7bbd4703fb1778d72214115dc200",
  "f9fc375d30b5626eced981d4ba80d2fcf6fba368",
  "01227f21040de0e7be4979604d23aaeb2d220d50",
  "1e53d5126a6f21a5cd9945ce4ae79a856d1c2aa6",
  "def7d9867c9ed2bcf49984cbe78066456175afa2",
  "2e1fc20df269fd7c6894c61c01f6fe0518029d38",
  "5d6c196729f7c0eb0850bd9093d0a018b62168ba",
  "062b7865763fd8cd0ad6079ec51a97c1bc35f88c",
  "4630931b71697d8ffbe6154c45be34251811e205",
  "a09166918a47fbda6c96df9a83f2e3b0df9057dd",
  "036e1c39411e8eb6fa3d616fcad19f92188de807",
  "8e6aee80cbffd0c0a3895a29bb029f57e1d76aec",
  "483a716335fd7a07acb9a8fdf759add85cd55ffb",
  "b1b1d87b55275de0f3b9c1a759ec6b543282cd5b",
  "cded9ffcab1c2fc873af9650ae35004160b39410",
  "37cc453cada7173368bfd3ed7c86c053557e5926",
  "8538eda858022257c393f2b7d72291b2a133f452",
  "d68841c1696583e487cc09a4e01a27afc4753bb9",
  "c29fa22be5cbc683d781ce42d325830b4337a62f",
  "28863c5a458f53c87559603b6bdb2e890ff002da",
  "5e4e15446aeee7ea6989e2502b20b1278ee81768",
  "25cf8915d7e4510f14f83d5317e6535d6e473bfb",
  "3e602c716c72f31569c1ead4ca6b8781d15f9866",
  "67e03a7960ccb911c4394671aec77d22f07cb495",
  "e2b3f1d1f69d2b555083899700cadb4a971349b5",
  "6c423e4662e730b3885e3375ee6d914612d5867e",
  "1694013c7d8caf3b3c577c8024ef1c58f94b7955",
  "91630edf6358ff0411a23f0a95ffa693bae1323b",
  "028454e0ff1e27ebd16cae59b2da633d377204c7",
  "0d07cb105767718dcaf998f307d4a97a38b35dea",
  "23c3569fc657d3a4b1bdde834df0c8f6ffacab11",
  "73c30d2754cfd13d6ac47ef28af974bfb021a121",
  "055890aeb6273f7a6ab5176722418048a03d3461",
  "3b89112c4fdc7e3fb8dded5157ae95c6afb68da3",
  "7cb3cfae1db1575b52d02afd3d12f27fbfd6b56c",
  "a310e3d7c808c74a9a2dd611d0bd6eda1f5f5340",
  "f329178028da5004aabd83549936ea9728326736",
  "5578dbecf4f35c97fc8762721ae16e010e42330a",
  "14020d1fc290f5a4c1feb06d970b395aa2d60518",
  "a1b2ffe5722b3d68d3dfbd1d3135c98681f1b480",
  "f3b3996a94517365815ba8bfd31306483c453afb",
  "cba0a45d7202f78c1e1ec5f150a1361df0565553",
  "dbe1feeba6cebaa82465ff34ac85324eb99bbd96",
  "067fac1d8369638e135bebaa5fc24648efe539a4",
  "18983e0eba9f797a5602dacb9e3a1fdb1b0e5b8c",
  "9f5445a4bbfd237564917d8749986798d61964c1",
  "79025990785dd192d5732f072e29a37728a05109",
  "a7caf5831836aef6ac5e6726a05f807ac20bbebb",
  "23027cde1334d6db48868b8dadb94cd027b9b7bb",
  "d0b280d64748bfc59a7da25bf640aa2d5462266e",
  "8a9c5dac4ddf028916e6feef81ec0cb670f1e713",
  "3790e9a57245215e68c06879cfb3d49ddf511f11",
  "a5004ed91303ead3670260a0e682726c42cee57c",
  "23e829a6706142d16305cc8f7f8c8b9bd8ffc040",
  "7e592d0d2c566b32b7c1e44b3413354cfae15e4e",
  "2e7a1685959b20ba75ddbce3db38798fc18becab",
  "82218944dfd3501a3d4705c5132ad06506372a0f",
  "ef4930e12ae3838d6059cf4990c8a0c2f6669c59",
  "574f7a6ca7a130635f84701294f347ce26d2d586",
  "5c91c2f83ca9daa19786263acd958bff2c79ca44",
  "65d838dfb75cda0055db5fb03f12008ede246a3f",
  "3c29ee4da5392eb1bdc9eb39068ab6a870d0c16a",
  "f17a673f3438bc7d8e0b0b22ccf20e4b868f0ad7",
  "653bf84319d61c7b41ad67b7648c8ee8571b6a16",
  "3187b6d0e15a37687fa6a8683d54e2fc5c3a13da",
  "4c29e4987613d1b30fdeff0a6af7a91b3be543f2",
  "ee68df44ba84a65ec112d289100ecf978485c7d0",
  "59283ef51d65bf7f7b7f430059aea19533f780b4",
  "7694f04e3be4bea0e35f95d4728fd65cc9ef46a7",
  "dcca8b27811f93142ec2bc14762593193ea69147",
  "20115938f5b50616fca15cc1816b28423c2e016b",
  "07b7e2a3f9733cbff1035533d0f2ba66008266b6",
  "cd2d04dd8bd78ac250a2adebede35802ad117110",
  "06e86e3d4a3f735c915a770fdff73ca8bc610476",
  "3014039565f5e568630f7e463c35475bdbe697c9",
  "eb729c4de8839c4123d0eb24d1d35886286ffff0",
  "c990f68c512ecc7c23ec6ff428d51300d6425dc2",
  "f3df0f4508b4cfe7e720f830f560c4e10f900703",
  "43ff171136ab1855eb37721075a9208c1de3ad20",
  "5d487b6bd25daa126e8edcb23f70a87ce4f7a27f",
  "84f6f72a57317242849131eb3c6aac28cb01abd3",
  "fd583ad477087f488eacd4ca243f1c93f5dac09b",
  "ef3cb487cb03dfde3a33b592c24dff439ce9b783",
  "7bd47a7efc8448f750163b07c812654bfadbe91d",
  "b9de6e1facedee977ccd4b30aea8fe957a0ae09a",
  "4ae009c0577ce4d0c87dcd743de9039ef050210f",
  "04280ea8afacc8b46982710da67a835b92275625",
  "ba7939b877ef0c1f066f0f6944b8c834f96fb67c",
  "bd735f759f8c653a215f2e9d2cc1d8a248a25567",
  "e9c70b7ab18d0b07580b80f2d92c43b11be5f71e",
  "795c10dada7dd963603073be205325324a1dc205",
  "8802f1d217906250585b75187b1ebfbb5c6cbcae"
};

const char *SHA256_sums[] = {
  "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
  "e632b7095b0bf32c260fa4c539e9fd7b852d0de454e9be26f24d0d6f91d069d3",
  "3bff939c10f4d9bc21c6944606bcb81901cbad80fc6801b257fd8aa127881687",
  "b344d80e24a3679999fa964450b34bc24d1578a35509f934c1418b0a20d21a67",
  "103c5169871d49be7a2ebf9e6fe4720244cbf1fdbccdbfaca489898ea069504c",
  "5845d549b3465df3c1fe755ccd99a9252858b448fa85fbd29139c3a33418a9ba",
  "2363ecd70a265e2233d2b8b0a703bcd6aa71dbf47a8716fcdb4b35ac4fded6c7",
  "883dbdc815a382a8ac863a990b4a33b601acfce6286df588b1e10416ca9934c1",
  "10ae0f24c936bc39be215f80c343c6e870f640fd56b0aeb842c3cd49a4e6dfa3",
  "3ba62773d07dd21b5712a1c221207bf2f46e459d862e7b7062b3b9e0073bbb1e",
  "1a90011d5a17cbd702ea49cddd28190439dfeec1710e0efe52315e034ef449bc",
  "030b6b1f71e51020e7b34f753d26741e7ed7c5cac3324b4fb237bf7f190326a1",
  "a83b8899ae591254330a059b8c5c5a0d61b8a5cb1e20cd43cf62ea950861a108",
  "8536a46b036db54a1f68389081f4c5dfb36c005ca655c0d005ade052e074fefc",
  "3b6052bcafcb593a2b44229d6418f3638a1040ede220a06186948e0bc2378e10",
  "9bc94b608c3636f6dbd12a7a08e586f2529c1910465cf764e5a2a16260a15c3b",
  "1b0b70a113cd4065b095bae73fba840f3b93912e89dd535f7f795912e9b307d6",
  "33a753c1d23f6a539b55c5c35dc0174ae048bbe517c701f3959495d509b862c1",
  "99159403f98a4d80adb6234c336029f32c17efdc70f1d412b7e6008d6623f3fd",
  "5cac4f980fedc3d3f1f99b4be3472c9b30d56523e632d151237ec9309048bda9",
  "b29d66e56ed90cce9b0165c43fedec612b60a071974d8be4513e18580d55b5bd",
  "60985d1eccaf8f3b95df873307d4727bc7af67dedaca6ea3d00d7e80dbb9d95c",
  "0ec4cdc3ab31a48025746379b070b1af6b152e6dd1eefe8a16d1855c85711d72",
  "76169b1e79ed4d640a78d664fdaced5035e7e0f116d7f044169763763a73d6b2",
  "cebf42910d175773a31cd23fc7c08eaddba11c267105e51688728efd6152f798",
  "8df831769cd51e4f57808343603e97c1ea44fcab46bb595a5000b9ad1d03bd70",
  "4e866f068eb39bb4465a3185badc58f8be565b3cbe0d8e79d0c893dd92ca99ae",
  "4a7b18fd0454f18d0ad320d8cf874e0466490e327bc3ca3beb13b1cb0fb01fff",
  "a5e86ccb68457b2e8e5591e3c132ed5f824480ab3b34e8b798b1b4e955cc2bad",
  "6c007ec72ab6d8bd1e7e2b90ab06095d38d042c172100b5364687985cccb71d5",
  "588f6b03a29d124ef050bc1e46bb60cd983e3d75bff45b6f1438cb58baaf1a9b",
  "ce32c090e5e13b6e5967e71e0d0025ca61fb6bcd54502221e354535ee7504fbe",
  "5f48828a7ecafc69180e8e9607b277b3dd17e53acc043412a06d8f170711c74b",
  "2d79fab9bb7d5b49e4c7eb28c14334f9d014129ce43d1252636b23ecaa569771",
  "acbe47d52e08dc6ae67b0bc249c6fe92c2fea7cb5d168d089bdb4e5f012a70dd",
  "177264d66f016c32fc7a4bf3d6a18fe64f3b92aa25dee9c3b84e6e2d3dba2467",
  "41555a329cd561031b7f79aa7ffe614aa341fa4c8f67be9d3169ca02ac513951",
  "6c450daf0a44317b850ab800b2986e3bfa19b118d82de07331c59b4461e08bb4",
  "72a0280b4079082c4823f72d5847038ca4b3d689b8d4de7f4b8565ca5cc59ad0",
  "e79df309e6b0e98a1b677e5d47765063170fd0fbe136d305230dca2ca1ade525",
  "119ef8154ecb9f78200ab9a95930877811261da37f9cad9e533ad34a57275fad",
  "fd535438ba7bc96dc5aae8b19059fc4307c0e2df4b252dd0d4d10dedd3116fd9",
  "677b9fdbe2bd79af033c224b32803a77dd284885f8655aff914ac63fb65c0a70",
  "d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592",
  "ef537f25c895bfa782526529a9b63d97aa631564d5d789c2b765448c8635fb6c",
  "88e197dce3e2562b9fb62bfdfb92c525328742af370fa2cd7c7bafaefb38f09c",
  "6e186b825513e046ba1d030f5bd31caa27a486bab8933e3799e8fc8c7a0be919",
  "ffe66f70564e2ef5b55cc4083aa1bbc24169c799a624d98182f99b8a7c950a82",
  "381ba8d74f62ef53fe4d22511c9d7c9f182d719e8073a5ab0201f91676a2ee86",
  "0147a26010960f5db71fcfa15c6f9278f2556905aa9fce122bbd5fe787e3d934",
  "fb736023fbce2dd88d6eeffa02dc975f5b3cfa0d2c0641382ace3cf92975bda8",
  "7c17ff3bf15c19d9a78f5c3f60dc38fab533ece520c8b8c73fcb0fba670c76b3",
  "e32271566d6a71b90285b5d00447d1f27737d56bc14b17efea026c78e27af416",
  "6867916bb6e48ee4f3b3a9eb4630233ec89fcf3722ea429ef300139d74f1f18a",
  "5a0e44a7c154b01f19a6cf5d83d8ea556d17ba1ffeb05bfcacdb7c477dd1c912",
  "0e9bc14d279f681c01eca319b7c22bf6e313186865a4d2111712f29ecc0223bf",
  "1be2cb604f04f8538e1ab595dcceccf0b838041e72a4dfde8df53d84fc841828",
  "0415d70cae1ca48b070e789748e8f3982a209a0c4b8070e2d3a26f729f04b0a6",
  "0e29d748b4cca4b372d587ab8164361aa127664635f956fbbdf076c36ffb0c9b",
  "8b0ccd3d72a10e396b16b67980f31823972b7114059d0d780b7c6c1d11aaab73",
  "7105f8ae45fcb1a1829053f98681b526616e1d6028d1f72a6a0cea1e079c2aaf",
  "5ab206331d14b2216b02eb0a58388e8209ffb396bc54eb22a47634cf236a03b9",
  "71daf2e02b4b542a8064567793b62fed41f2241dd284163b15d02d279910e1d6",
  "795a664f3ecfa5003b7d18e8ac44d88ed49a8ad731238e381f76cc72451e5d49",
  "0d01316239b68e707e8079f02588bba156906aa0a8b328a2103f3dbe79464272",
  "53798a699aaf9b5992322e27a7c48802ff41d04acc52c1e6657fdee037f9c0b0",
  "250676ab47b392eaeb3bd8f7640c676e5a9fcfed22dc08948601c68d7eb867e5",
  "c8c295b3179d555b5e04c82f8834b031d4dcb5df9409081e6e9b23be4d1aeb93",
  "a6265afb2182630750a70887a35072908c048d5f9c831a2155da1887f1dd7709",
  "78ba265740cc1335d27530a52dc456668c9475250d83f3e1c3041ab3d0856338",
  "490b607d2009507689d5ce40f964e9b5c56ee54d13d99666eec256439a5d7691",
  "012c3b2137fbb69e1b1457499923622d7a6639c3fcfd0c1889de9f1ae9a5224c",
  "47f57d4c0eef68f4b14a02295da342bba8be6ddf901ed4ae1eaf7c3306672593",
  "33eea677868305f597087e15be83723efd51e1f55342dac47afb604579fa0f74",
  "f9aab1fa5ed80cd385cf625ec808339d819bd1faee979c3ee008db68db19e6bc",
  "1e6279781c1a757c9cd3aaf2665c0c1d235e514065f57dff455256896313c5ae",
  "fcad8c2b8ab78e1eb313f9a77b85e29ed86d4468d78e845fe7b197cff28889a0",
  "0cc46a7fba1d7b1e7a7c6c438352fdde342c573550eac5a177e38d0cfd854b91",
  "7d64ff1a21b7194e2a34f718bf536f4fbb636ea2d50b9de9423c1a64da67a566",
  "624097dd2a64d12dbd7a9d15d58b6a31a8c11e0be67f20afd388e61ab316d6d5",
  "c10ed525d528079a6ac6e6ebc51bb439a48df167c6860da2dcd8ef5a101a4bf9",
  "b9ce9b34346f2d83dc60927231c14d1af0b1a915514d610cbdd69a8928ae1b57",
  "4a3194983f551da64720e60b91e0bfcca2c5f7277b97ceb813b6665cbecf5078",
  "cac95b35edebc00cb109d4726befb06adbadec365e102f8c9c024fec2efedd93",
  "bd284ce312ff8f71a8fffd5737733c72dee0199eb5d9dea29875b02fe7dec138",
  "888f4d527281b7ca77fb63651ea8c28850d62f38d6918a178bc7de7ecd61aca1",
  "50839952e08506f523696a35e758eed06d7fce0a8e4c079242bd15b476dc2632",
  "ce6b0b2e2494ba591909f5971d4a326c395f47d45ab2389fc5980a8d7c160373",
  "328524b5f7c5de2b6fda754cd634480d2ae9953514e208d93c7b0493de3c376f",
  "00e6bbca7e9f230b903d0029a603831688e37e141d283a88ff65f8a8de711214",
  "e9419c75509f476ecd71c0ce5de42b13b70665182d470dc6b9389992e71ca610",
  "bc93bf4ac98f5e62a180219b7cae5fe4b1a33700d1abd8769310f1b9c458052e",
  "b59cbe76a3a993a8a5e93e7fae2277a99c52b27570f8cec0fc27c6407b87a863",
  "7b977d99df79f3c123a551339a3584e1dbf8c6b220489c94e8b5ef241a2f4f32",
  "42da1a65ef28c00d30b63128ad839782daf8437da50eaedf9e40c05daa324030",
  "27b7b244d0a284afc02b21ddf8818d4934bf7d4a96db6c9be02b9a29f1d3e877",
  "69e8ebc88995bfb9af4938fac297e7cc87f516d91ee3db9c385051aa67bfa291",
  "e97ec334ea0e600801845a004cf943282716e537d2fb41edd3252ecc604cb868",
  "61ddc6c83fcded7492a0b4e6682a2ec54ea79bd832ffacebd13eec490ae9c513",
  "b1b2e4d6d5f02ab694d8be129dbf9f7fb345190927fd2732ab24e395ef877a95",
  "036d3ac977186da97d849ae8706f573bae36822a83a8b820b0b09bfa7a4fde52",
  "244dd1e7818cc1fc0b1790e5bdd79df79720b5ca4b30ddfbc6e03d2fa80edf24",
  "025dd4c8ae7d9f3aec6b2e3014eda38ec54898c67de9ee68578ec7cc8254c345",
  "e29858f925c90e19c49336f52a8acf57e7a0f10fbf1b0254ec9926afc77d34dd",
  "e6ece3c684d5874497b83f6b486f0dddef4377f914e19ea717b82426d6ca37e3",
  "952c6da8834e0c4c127269a6e69c59a23af9e35ed70577715979075324776eb0",
  "675a0a83882910ca29d9a4b72e278afa307a2661bee3f28dee7faa7db73dde73",
  "4102eada32bbc31c13f1fbf2f039bb7a46bdb3589e9bb3915046de72c0c2ead1",
  "305793f522114ca65e243f80b82199425286a07585deff0d132223506c54c48a",
  "c666ec59da13eae8361c08bae009f114641bb3bed6f6c88c69c888ab9b9bd2d7",
  "115ad98815bdfbc2e9aa0922a63c530f2f49bb36bf339345694b6cfadc5a25bd",
  "1186297e299b427c8ce24e20670156fe85eb9102f8ed7104154fbd10ad28b49a",
  "2d02d02abca735d371fa9fbe2ec1fcf5c02a8eb5186140b849d13d5667c8588b",
  "c8357ae61f0c6107d48ffd35b791f2a96c36d9004acbf97a7a6fe1941096e74c",
  "e2f783571644ff40bb649ee1a6c7481e288eae50bd9621c638102c1222f02695",
  "b057d8b05d77dfd016c7820ee32b3dcf8c0af73f79a003a68f7b344bff5f9489",
  "f98a7811608e9f78df7c1dcc6765ad672d907ab49e3ab756b6ad2ff392ae3cb0",
  "06727bbca9d6e47cbd4e2f61b313627cf0489c5f84850dfb45cb496f11e0d880",
  "62e011d19bbb328c57808bb4dcb1fd25551a642df179615559a654e91b233afb",
  "18811c3a1798f207c75d895a6deb4b2ee05a27749e5d4dab02f5299f8f62e43a",
  "a2eec6a9e819ca9ae6accd714273210cad3a98ea104661b841b8b18fd695115a",
  "b745658efb45b83211abaffe3af0e5fd3769866d154194c9078da9491f793bae",
  "bef6454bcf2dd622f73ab849166a95f56be540ff05cc2b79412f40c60cfec3b3",
  "13f42a4a6df75f6b09a53eff4a92b824b8212ce99b54169774958debe92ba00f",
  "f6addf5f0a754434e6767535ee8cd12a57d3c78eb5925d421e43870ddc0c4b02",
  "abbd74e4444bcf0a33da28cd9b74483d19c07c0c84c7a217ed1d8d143da44c4c",
  "18c5fb1bfd33fc27a0b7799eb14d502e8b59acd5da0be6f9a7fbabd96608c61d",
  "91a32360bd0152180990285fd7cb3145207d33f866c9d99e7f8bb7331a12d03a",
  "3324ebb8bfd51c9ac3f3994a56b7e0c0106d9d938c147edb391a4bf812d6afb1",
  "914e88337910ee43d63f77d91502eebb35ae38ac6138bd7af4d879dbb730ac85",
  "bc73865737be6195981507338ef06ec2a5f34d3f12580b4f89d5e28ef8283969",
  "0b41f57008120081011a2ba580d8cff17f9c1f3b2e811359cd3ecfa9b36dc5e9",
  "a1702789897f4e641bf00d505549c6dc9df9daf904f3267e0cb583c7fb49e832",
  "70737787a53182c78152e845e0d803171d27105c7ef9407b48ae51280b0b1ed3",
  "683a017524f641b4c38c26db0df5046fbc38e30fbbe7fb7a6804e2e039c9d353",
  "8bbd8c3f3c6911a3e73ba7a480f902a95fdf4c8a7c554b68e7330e4914481f15",
  "66e62f07828e8a8a6ce821cb29fe34f2ec551d4422b593380e5209ee4a3a3e57",
  "2aa054e91da4874329ac8946922323c8d5b114b4ddd714f54cb1fb069dc56646",
  "47db1856215834b20d70031695491a4a90416bac8d231646bba8754585f67d08",
  "eab539981a22c36e481b71d2c828b848b9b127963d7b5eb56c4903f5cf004296",
  "cf43ef0749885e4108f8fc2774a840264980e4f2be51d1c803bbb90965745034",
  "fd6847b7d5ea924beb8e7d43d0e87d4866f9744629f2768cf32e7f37efd23253",
  "1c3d53f1a7fe78c34a4c33331126375e57f4f8f732d39e0ff550fb717e683724",
  "f03b454c7bf5ddfe083798a85ac46bc671ef76b381b969ab4f333c74397693ab",
  "0c7255ee15ceac49e1281447b159ed1ccb8fa09d3d002fe3337c80f75a247b86",
  "4c69c21e1afa642423a660359e058c8d6a2dae61c1083b7dea46471ebf24f0da",
  "b984e785026dabfa52ece12495df98bf80ba831ea316c08fc4b39c5fc00b50ed",
  "40b33b1a89820917e19e95bf5abae2121b8f200c826a3559440010d2863a5acd",
  "053de20a192f3205f46e3f68d8b9926abcf64df55d01cf166e7f8e8c8d042487",
  "ababd9164d854d8a7b56fc4e6980dbafcd5aa017f5e2b5777a6e6e47460fc716",
  "f3982fa10d2353163d644ab33e2c5af7264c0c9c8b14cd88d91331b5d01ae3c7",
  "0d7c2df609dc5c44677d62b8839576b98ec78fa8b5913add17b7e9cfaa6aa75d",
  "3b86e1a3a4e3cf19734b693cc3d9b24d4173b5e8ace1be3daa303755ce8d5737",
  "dfcdb86a6ec326f0f4c8b167b5945979a5cf3a2ef20970c47b46ddd47f8fd6d1",
  "e2a696a14922cdeb99abe04a66576e65142be3b0e53cf0c0f05c86acf63bc83a",
  "780646dc52688aead41076d4906e17b42eb5593565f179a6bb5135143d40d03d",
  "847ed344db2cdbfb7f69f9b2c9a5359e13df72c2485345a80fa9b114ec7c8c03",
  "a4f5b2a505437424c3382e2d534ed2fdb55af631c5b211871f2e62acb5dd722f",
  "e6e8883f5c8d840d7895afac181c6d9fb154672fb2c7ba9757ca8528242bef64",
  "c89e7de64979fcbf929148c7b44322047e820219854600e88f7a7ce805971c38",
  "591555d8d3936620ebb6be7549ea9eaafa9e6a562b9ebbbf4c04eb4f926d5060",
  "2ec1da3a8252e21834db7c90077b12547f70890b853b5b269a38f74b421f3a4f",
  "3b05f141c3855409941c6596a92ea7a3ab59764bda3cdcc6812060a5e5d1f48c",
  "82b21ff095df092358450698e7a534453105014f3b227a210cb5d523191570e8",
  "229da5c29efe0885663587fe0080862ef52e7504ca64f5d6ff1c26f5a7b1c0c7",
  "cd3c1d86961be993a150c1126a958ef14a3e47ef21507492ffdee8b089774505",
  "e346ecc2f3e8cbcbbead67341edb971f2a9e152f8c1e086693dce431d9e14335",
  "5e5c06dc93c409e935b87373f2647f57a951118851b226f908751bcafb496b2a",
  "2f5ded0589de3ef9f5e5b05df0a19b02fcee0e686900c5eb9e3153ba3ccdf685",
  "6a0335f78e0fea8e4cdf747d6464f2de78e659b9de5be37ccf8f81f1e775ca79",
  "8adfeb35e7d07f4aece0f8b4b282a303e45b11c9b4f9b1798cbcf8cf0dc5f48a",
  "94dc98b89a5b498d7c7eb0fb0524af296d0181e7a4dac82c3bd7ce147019b52d",
  "4b2dae26d837294c81e00c6c28692235a9ea046bc8038ea78ce1819cb5f54be4",
  "77d9e99e3a956c9b52742b498b8811cb721ad798866d36d269b4b554a707e63a",
  "652082a8998da5439cb5e695104febfa81d3d3a0bb4dfd49120b82e350b48f6f",
  "43bf07481f0bc237e1ed2ce2b0b3cca1989f9bdbbc7cf1e78879984ff927b3e1",
  "648f7216f324f0a46648d757a21dc25c9382c64a095ea95b62aed37596bdf842",
  "34c3d02b75da5d2739bb8d4916110469e1b854a8104aeec7ccfef52a02f234e1",
  "0d0b8d475cb50a40e2cb999757106f4576c5b69176df4c30e1c4659de1468ff8",
  "63d7e84cef1bc8c74ebdf53fe795766f0fd32a9c6246586f8217010db1c2c9f5",
  "99525cf2ec889a1628576099f34ece6d60de03fa85ade70a3d0913033934dc1f",
  "8aa3e3cd4d678c9623caebac79ecd62fdcd15de5960c7fbffc3ab8e77788109a",
  "c71259d6ad975ada31990fb7b3aa958248bd88d3563b581959acf4f18310f266",
  "df3a0c35d5345d6d792415c1310bd4589cdf68bac96ed599d6bb0c1545ffc86c"
};

typedef struct {
  GChecksumType  checksum_type;
  const gchar   *sum;
  int            length;
} ChecksumTest;

static void
test_checksum (gconstpointer d)
{
  const ChecksumTest *test = d;
  GChecksum *checksum;
  GChecksum *checksum2;
  const char *p;
  int chunk_length;

  for (chunk_length = MIN (test->length, 1); chunk_length < test->length; chunk_length++)
    {
      checksum = g_checksum_new (test->checksum_type);
      for (p = FIXED_STR; p < FIXED_STR + test->length; p += chunk_length)
	{
	  g_checksum_update (checksum, (const guchar *)p,
			     MIN (chunk_length, test->length - (p - FIXED_STR)));
	}
      checksum2 = g_checksum_copy (checksum);
      g_assert_cmpstr (g_checksum_get_string (checksum), ==, test->sum);
      g_checksum_free (checksum);

      g_assert_cmpstr (g_checksum_get_string (checksum2), ==, test->sum);
      g_checksum_free (checksum2);
    }
}

static gint
hexval (const gchar c)
{
  switch (c)
    {
     case '0':
     case '1':
     case '2':
     case '3':
     case '4':
     case '5':
     case '6':
     case '7':
     case '8':
     case '9':
       return c - '0';
     case 'a':
     case 'b':
     case 'c':
     case 'd':
     case 'e':
     case 'f':
       return 10 + c - 'a';
     default:
       return 0;
    }
}

static guint8 *
sum_to_digest (const gchar *sum, gsize *len)
{
  gsize l;
  guint8 *digest;
  gint i;

  g_assert (strlen (sum) % 2 == 0);
  l = strlen (sum) / 2;

  digest = g_malloc (l);
  for (i = 0; i < l; i++)
    digest[i] = (hexval(sum[2*i]) << 4) + hexval(sum[2*i+1]);

  *len = l;
  return digest;
}

static void
test_checksum_reset (gconstpointer d)
{
  const ChecksumTest *test = d;
  GChecksum *checksum;
  const char *p;
  int chunk_length;
  guint8 *digest;
  guint8 *digest2;
  gsize len, len2;

  checksum = g_checksum_new (test->checksum_type);

  for (chunk_length = MIN (test->length, 1); chunk_length < test->length; chunk_length++)
    {
      for (p = FIXED_STR; p < FIXED_STR + test->length; p += chunk_length)
	{
	  g_checksum_update (checksum, (const guchar *)p,
			     MIN (chunk_length, test->length - (p - FIXED_STR)));
	}

      len2 = g_checksum_type_get_length (test->checksum_type);
      digest = sum_to_digest (test->sum, &len);
      g_assert_cmpint (len, ==, len2);
      digest2 = g_malloc (len2);
      g_checksum_get_digest (checksum, digest2, &len2);
      g_assert_cmpint (len, ==, len2);
      g_assert (memcmp (digest, digest2, len) == 0);
      g_free (digest);
      g_free (digest2);

      g_checksum_reset (checksum);
    }

  g_checksum_free (checksum);
}

typedef struct {
  GChecksumType   checksum_type;
  const gchar   **sums;
} ChecksumComputeTest;

static void
test_checksum_string (gconstpointer d)
{
  const ChecksumComputeTest *test = d;
  int length;
  gchar *checksum;

  for (length = 0; length <= FIXED_LEN; length++)
    {
      checksum = g_compute_checksum_for_string (test->checksum_type,
                                                FIXED_STR,
                                                length);
      g_assert_cmpstr (checksum, ==, test->sums[length]);
      g_free (checksum);
    }

  checksum = g_compute_checksum_for_string (test->checksum_type,
                                            FIXED_STR,
                                            -1);
  g_assert_cmpstr (checksum, ==, test->sums[FIXED_LEN]);
  g_free (checksum);
}

static void
test_checksum_bytes (gconstpointer d)
{
  const ChecksumComputeTest *test = d;
  GBytes *input;
  int length;
  gchar *checksum;

  for (length = 0; length <= FIXED_LEN; length++)
    {
      input = g_bytes_new_static (FIXED_STR, length);
      checksum = g_compute_checksum_for_bytes (test->checksum_type, input);
      g_bytes_unref (input);

      g_assert_cmpstr (checksum, ==, test->sums[length]);
      g_free (checksum);
    }
}

static void
add_checksum_test (GChecksumType  type,
                   const char    *type_name,
                   const char    *sum,
                   gint           length)
{
  ChecksumTest *test;
  gchar *path;

  test = g_new0 (ChecksumTest, 1);
  test->checksum_type = type;
  test->sum = sum;
  test->length = length;

  path = g_strdup_printf ("/checksum/%s/%d", type_name, length);
  g_test_add_data_func (path, test, test_checksum);
  g_free (path);

  path = g_strdup_printf ("/checksum/%s/reset/%d", type_name, length);
  g_test_add_data_func_full (path, test, test_checksum_reset, g_free);
  g_free (path);
}

static void
add_checksum_string_test (GChecksumType   type,
                          const gchar    *type_name,
                          const gchar   **sums)
{
  ChecksumComputeTest *test;
  gchar *path;

  test = g_new0 (ChecksumComputeTest, 1);
  test->checksum_type = type;
  test->sums = sums;

  path = g_strdup_printf ("/checksum/%s/string", type_name);
  g_test_add_data_func_full (path, test, test_checksum_string, g_free);
  g_free (path);
}

static void
add_checksum_bytes_test (GChecksumType   type,
                          const gchar    *type_name,
                          const gchar   **sums)
{
  ChecksumComputeTest *test;
  gchar *path;

  test = g_new0 (ChecksumComputeTest, 1);
  test->checksum_type = type;
  test->sums = sums;

  path = g_strdup_printf ("/checksum/%s/bytes", type_name);
  g_test_add_data_func_full (path, test, test_checksum_bytes, g_free);
  g_free (path);
}

static void
test_unsupported (void)
{
  g_assert_cmpint (g_checksum_type_get_length (20), ==, -1);
  g_assert (g_checksum_new (20) == NULL);
}

int
main (int argc, char *argv[])
{
  int length;

  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/checksum/unsupported", test_unsupported);

  for (length = 0; length <= FIXED_LEN; length++)
    add_checksum_test (G_CHECKSUM_MD5, "MD5", MD5_sums[length], length);
  add_checksum_string_test (G_CHECKSUM_MD5, "MD5", MD5_sums);
  add_checksum_bytes_test (G_CHECKSUM_MD5, "MD5", MD5_sums);

  for (length = 0; length <= FIXED_LEN; length++)
    add_checksum_test (G_CHECKSUM_SHA1, "SHA1", SHA1_sums[length], length);
  add_checksum_string_test (G_CHECKSUM_SHA1, "SHA1", SHA1_sums);
  add_checksum_bytes_test (G_CHECKSUM_SHA1, "SHA1", SHA1_sums);

  for (length = 0; length <= FIXED_LEN; length++)
    add_checksum_test (G_CHECKSUM_SHA256, "SHA256", SHA256_sums[length], length);
  add_checksum_string_test (G_CHECKSUM_SHA256, "SHA256", SHA256_sums);
  add_checksum_bytes_test (G_CHECKSUM_SHA256, "SHA256", SHA256_sums);

  return g_test_run ();
}
