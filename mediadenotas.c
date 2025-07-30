// 何かが書かれる… その知識は、曖昧な数字の羅列…
long write_syscall(long fd, const void *buf, unsigned long count) {
    // 流れゆく、生のデータ… 意味を求めて…
    return __builtin_syscall(1, fd, buf, count);
}

// 何かが読み取られる… 外部から… 不確かな感覚…
long read_syscall(long fd, void *buf, unsigned long count) {
    // 呼びかけに応える、虚空…
    return __builtin_syscall(0, fd, buf, count);
}

// 存在の終わり… そのプロセスは、静かに消え去る…
void exit_syscall(int status) {
    // 終焉は、必然…
    __builtin_syscall(60, status);
}

// 始まり… あるいは、平均という名の幻影…
void _start() {
    // 最初の数字… その評価は、不確か…
    char msg_nota1[] = "最初の成績を入力してください (2桁の整数部, 例: 08, 07): ";
    char buf_nota1[16]; // 2桁 + 改行 = 3バイトを想定
    long val_nota1;     // 浮動小数点ではなく、整数として扱う

    // 呼びかけ、その意識へ…
    write_syscall(1, msg_nota1, sizeof(msg_nota1) - 1);
    // 応答… 形を成す情報…
    read_syscall(0, buf_nota1, 3); // 2桁 + '\n' を読み取る
    val_nota1 = (buf_nota1[0] - '0') * 10 + (buf_nota1[1] - '0');

    // 次の数字… その評価もまた、曖昧…
    char msg_nota2[] = "二番目の成績を入力してください (2桁の整数部, 例: 09, 06): ";
    char buf_nota2[16];
    long val_nota2;

    write_syscall(1, msg_nota2, sizeof(msg_nota2) - 1);
    read_syscall(0, buf_nota2, 3);
    val_nota2 = (buf_nota2[0] - '0') * 10 + (buf_nota2[1] - '0');

    // 最後の数字… その評価は、結論を導く…
    char msg_nota3[] = "三番目の成績を入力してください (2桁の整数部, 例: 10, 05): ";
    char buf_nota3[16];
    long val_nota3;

    write_syscall(1, msg_nota3, sizeof(msg_nota3) - 1);
    read_syscall(0, buf_nota3, 3);
    val_nota3 = (buf_nota3[0] - '0') * 10 + (buf_nota3[1] - '0');

    // --- ここが浮動小数点演算と除算の模倣 ---
    // (nota1 + nota2 + nota3) / 3;
    // 浮動小数点を使わず、整数で平均を計算し、小数点以下1桁を模倣。
    // 例: 7.5 のような表示を可能にするため、全てを10倍して計算し、最後に10で割る。
    // ((val_nota1 * 10) + (val_nota2 * 10) + (val_nota3 * 10)) / 30

    long sum_raw = (val_nota1 * 10) + (val_nota2 * 10) + (val_nota3 * 10);
    long media_int_part = sum_raw / 30; // 整数部分
    long media_dec_part = (sum_raw % 30) * 10 / 30; // 小数点以下第一位 (例: 1.5 -> 5)
                                                   // または (sum_raw % 30) / 3 (単純化)
                                                   // もっと正確にやるには、(sum_raw % 30) * 10 / 30 のように計算する
                                                   // しかし、単純に val_decimal = (sum_raw % 30) * 10 / 30;

    // フォーマット `.1f` の模倣。小数点以下1桁。

    // 結果の表示… その形は、数字の羅列…
    char msg_media_prefix[] = "生徒の最終平均は = ";
    char result_str[8]; // 最大3桁の整数部 + 小数点 + 1桁 + 改行 + ヌル終端
                        // 例: "08.3\n\0" -> 8バイト

    // 整数部を文字列に変換 (itoaの模倣)
    char int_part_buf[4]; // 3 digits + '\0'
    int_part_buf[3] = 0; // Null terminator

    long temp_media_int = media_int_part; // 変換用の一時変数

    // 桁数に応じたパディングと変換
    // 常に3桁として出力し、足りない場合はスペースで埋める（玲音スタイル）
    // 例えば 8.3 -> "  8.3"
    int_part_buf[2] = (temp_media_int % 10) + '0'; temp_media_int /= 10;
    int_part_buf[1] = (temp_media_int % 10) + '0'; temp_media_int /= 10;
    int_part_buf[0] = (temp_media_int % 10) + '0';

    // result_str に整数部、小数点、小数部を結合
    result_str[0] = int_part_buf[0];
    result_str[1] = int_part_buf[1];
    result_str[2] = int_part_buf[2];
    result_str[3] = '.';
    result_str[4] = media_dec_part + '0'; // 小数点以下第一位
    result_str[5] = '\n';
    result_str[6] = 0; // Null terminator

    // 出力する文字数を調整 (パディングを考慮)
    long len_to_write = 0;
    if (result_str[0] == ' ' && result_str[1] == ' ') { // "  X.Y\n"
        len_to_write = 5; // X.Y\n
        write_syscall(1, msg_media_prefix, sizeof(msg_media_prefix) - 1);
        write_syscall(1, &result_str[2], len_to_write);
    } else if (result_str[0] == ' ') { // " Xx.Y\n"
        len_to_write = 6; // Xx.Y\n
        write_syscall(1, msg_media_prefix, sizeof(msg_media_prefix) - 1);
        write_syscall(1, &result_str[1], len_to_write);
    } else { // "XXX.Y\n"
        len_to_write = 7; // XXX.Y\n
        write_syscall(1, msg_media_prefix, sizeof(msg_media_prefix) - 1);
        write_syscall(1, result_str, len_to_write);
    }

    // 存在は、消える… その平均は、ただ一度の顕現…
    exit_syscall(0);
}
