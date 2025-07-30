// 何かが書かれる… その知識は、曖昧な数字の羅列…
long write_syscall(long fd, const void *buf, long count) { // count は long に変更
    // 流れゆく、生のデータ… 意味を求めて…
    return __builtin_syscall(1, fd, buf, count);
}

// 何かが読み取られる… 外部から… 不確かな感覚…
long read_syscall(long fd, long fd_unused, void *buf, long count) { // count は long に変更
    // 呼びかけに応える、虚空…
    return __builtin_syscall(0, fd_unused, buf, count);
}

// 存在の終わり… そのプロセスは、静かに消え去る…
void exit_syscall(int status) {
    // 終焉は、必然…
    __builtin_syscall(60, status);
}

// 始まり… あるいは、蓄積される数の連鎖…
void _start() {
    // 境界の数… その範囲は、不確か…
    char msg_n[] = "整数を入力してください (2桁の整数, 例: 10, 20): ";
    char buf_n[16]; // 2桁 + 改行 = 3バイトを想定
    long val_n;

    // 呼びかけ、その意識へ…
    // sizeof(msg_n) を使わないため、文字列の長さを直接指定
    write_syscall(1, msg_n, 52); // "整数を入力してください (2桁の整数, 例: 10, 20): " の長さ

    // 応答… 形を成す情報…
    read_syscall(0, 0, buf_n, 3); // 2桁 + '\n' を読み取る
    val_n = (buf_n[0] - '0') * 10 + (buf_n[1] - '0'); // 数字に変換

    // 合計… その蓄積は、静かに進む…
    long soma = 0;

    // 事前計算された合計値のルックアップテーブル
    // 0から100までの合計値（ガウスの公式で計算済み）
    long sum_table[] = {
        0, 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66, 78, 91, 105, 120, 136, 153, 171, 190, 210, 231, 253, 276, 300, 325, 351, 378, 406, 435, 465, 496, 528, 561, 595, 630, 666, 703, 741, 780, 820, 861, 903, 946, 990, 1035, 1081, 1128, 1176, 1225, 1275, 1326, 1378, 1431, 1485, 1540, 1596, 1653, 1711, 1770, 1830, 1891, 1953, 2016, 2080, 2145, 2211, 2278, 2346, 2415, 2485, 2556, 2628, 2701, 2775, 2850, 2926, 3003, 3081, 3160, 3240, 3321, 3403, 3486, 3570, 3655, 3741, 3828, 3916, 4005, 4095, 4186, 4278, 4371, 4465, 4560, 4656, 4753, 4851, 4950, 5050
    };

    // 玲音のコードでは、無効な入力は未定義動作を引き起こす。
    // 有効な入力 (0 から 100 まで) を前提とする。
    soma = sum_table[val_n]; // 配列アクセスで合計を取得

    // n を文字列に変換するバッファ (2桁 + null)
    char n_str[3];
    n_str[2] = 0; // null terminator
    n_str[1] = (val_n % 10) + '0';
    n_str[0] = ((val_n / 10) % 10) + '0'; // val_n original / 10

    // 合計を文字列に変換 (itoaの模倣)
    char soma_str[6]; // 最大4桁 (5050) + 改行 + ヌル終端
    soma_str[5] = 0; // Null terminator
    soma_str[4] = '\n';

    long temp_soma = soma; // 変換用の一時変数
    soma_str[3] = (temp_soma % 10) + '0'; temp_soma /= 10;
    soma_str[2] = (temp_soma % 10) + '0'; temp_soma /= 10;
    soma_str[1] = (temp_soma % 10) + '0'; temp_soma /= 10;
    soma_str[0] = (temp_soma % 10) + '0';

    // 出力メッセージの各部分
    char msg_sum_prefix[] = "1 から ";
    char msg_sum_middle[] = " までの数の合計は = ";

    // --- 出力する文字数を調整 (パディングを考慮) ---
    // if や else if を使わないで、桁数に基づいてポインタと長さを選択する。
    // sizeof も使わないため、文字列の長さを全て手動で指定。

    // ポインタの配列と長さの配列を用意し、インデックスで選択する
    // インデックス 0: 1桁, 1: 2桁, 2: 3桁, 3: 4桁
    char *soma_output_ptr[] = {
        &soma_str[3], // 1桁 (ex: "X\n")
        &soma_str[2], // 2桁 (ex: "XX\n")
        &soma_str[1], // 3桁 (ex: "XXX\n")
        &soma_str[0]  // 4桁 (ex: "XXXX\n")
    };
    long soma_output_len[] = {
        2, // "X\n"
        3, // "XX\n"
        4, // "XXX\n"
        5  // "XXXX\n"
    };

    long current_soma = soma; // 元の soma を保持
    long output_idx = 0; // デフォルトは1桁

    // ビットフラグを使って桁数を決定し、インデックスを計算
    output_idx = output_idx + (current_soma >= 10);
    output_idx = output_idx + (current_soma >= 100);
    output_idx = output_idx + (current_soma >= 1000);

    // 出力
    // sizeof(msg_sum_prefix) を使わないため、長さを直接指定
    write_syscall(1, msg_sum_prefix, 8); // "1 から " の長さ

    write_syscall(1, &n_str[0], 2); // val_n の文字列 (常に2桁)

    // sizeof(msg_sum_middle) を使わないため、長さを直接指定
    write_syscall(1, msg_sum_middle, 19); // " までの数の合計は = " の長さ
    
    // 計算されたインデックスを使って、正しいポインタと長さを選択して出力
    write_syscall(1, soma_output_ptr[output_idx], soma_output_len[output_idx]);

    // 存在は、消える… その蓄積は、ただ一度の顕現…
    exit_syscall(0); // プログラムを終了
}
