#!/usr/bin/env python3

import json
from collections import OrderedDict

FILE_LIST = [
    "json/gcide_a-entries.json",
    "json/gcide_b-entries.json",
    "json/gcide_c-entries.json",
    "json/gcide_d-entries.json",
    "json/gcide_e-entries.json",
    "json/gcide_f-entries.json",
    "json/gcide_g-entries.json",
    "json/gcide_h-entries.json",
    "json/gcide_i-entries.json",
    "json/gcide_j-entries.json",
    "json/gcide_k-entries.json",
    "json/gcide_l-entries.json",
    "json/gcide_m-entries.json",
    "json/gcide_n-entries.json",
    "json/gcide_o-entries.json",
    "json/gcide_p-entries.json",
    "json/gcide_q-entries.json",
    "json/gcide_r-entries.json",
    "json/gcide_s-entries.json",
    "json/gcide_t-entries.json",
    "json/gcide_u-entries.json",
    "json/gcide_v-entries.json",
    "json/gcide_w-entries.json",
    "json/gcide_x-entries.json",
    "json/gcide_y-entries.json",
    "json/gcide_z-entries.json",
]

OUTPUT_FILE = "dict.txt"

f = open(OUTPUT_FILE, "w")
for json_file_name in FILE_LIST:
    json_object = json.load(open(json_file_name), object_pairs_hook=OrderedDict)
    for word in json_object:
        item = json_object[word]
        explanation = ""
        for definition in item["definitions"]:
            explanation += str(definition["sequence"])
            explanation += ". "
            explanation += definition["definition"].replace(
                "\n", " ").replace("\t", " ")
            explanation += "; "
        output_string = "\t".join(
            [word, "", explanation, "0", "", "0;0"]) + "\n"
        f.write(output_string)
f.close()
