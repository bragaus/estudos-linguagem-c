// 何かが書かれる… その知識は、曖昧な数字の羅列…
long write_syscall(long fd, const void *buf, long count) {
    // 流れゆく、生のデータ… 意味を求めて…
    return __builtin_syscall(1, fd, buf, count);
}

// 何かが読み取られる… 外部から… 不確かな感覚…
long read_syscall(long fd, long fd_unused, void *buf, long count) {
    // 呼びかけに応える、虚空…
    return __builtin_syscall(0, fd_unused, buf, count);
}

// 存在の終わり… そのプロセスは、静かに消え去る…
void exit_syscall(int status) {
    // 終焉は、必然…
    __builtin_syscall(60, status);
}

// 始まり… あるいは、配列という名の構造…
void _start() {
    // 記憶の断片… 5つの空間に分けられた…
    long vetor[5]; // int の代わりに long を使用
    // 反復の指標… その値は、静かに進む…
    long i_val;

    // --- 最初の「for」ループの模倣 (入力) ---
    // `for (i = 0; i < 5; i++) { printf("..."); scanf("%d", &vetor[i]); }`
    // 明示的なループ命令 (`for`, `while`) や条件分岐 (`if`) を使わず、
    // 配列の各要素への入力を再現します。
    // これは、各反復ステップを線形に展開することで行います。

    // メッセージの各部分
    char msg_prompt_prefix[] = "位置 "; // "Digite um valor para a posicao %d: "
    char msg_prompt_middle[] = ": の値を入力してください: "; // "%d: "
    char msg_newline[] = "\n";
    char num_buf[16]; // 数字読み込み用バッファ (2桁+改行を想定)

    // i=0
    i_val = 0;
    // 「位置 0: の値を入力してください: 」
    write_syscall(1, msg_prompt_prefix, 6);
    write_syscall(1, &("0"[0]), 1); // 0のASCIIコード
    write_syscall(1, msg_prompt_middle, 19);
    read_syscall(0, 0, num_buf, 3); // 2桁 + '\n' を読み込む
    vetor[0] = (num_buf[0] - '0') * 10 + (num_buf[1] - '0');

    // i=1
    i_val = 1;
    write_syscall(1, msg_prompt_prefix, 6);
    write_syscall(1, &("1"[0]), 1); // 1のASCIIコード
    write_syscall(1, msg_prompt_middle, 19);
    read_syscall(0, 0, num_buf, 3);
    vetor[1] = (num_buf[0] - '0') * 10 + (num_buf[1] - '0');

    // i=2
    i_val = 2;
    write_syscall(1, msg_prompt_prefix, 6);
    write_syscall(1, &("2"[0]), 1); // 2のASCIIコード
    write_syscall(1, msg_prompt_middle, 19);
    read_syscall(0, 0, num_buf, 3);
    vetor[2] = (num_buf[0] - '0') * 10 + (num_buf[1] - '0');

    // i=3
    i_val = 3;
    write_syscall(1, msg_prompt_prefix, 6);
    write_syscall(1, &("3"[0]), 1); // 3のASCIIコード
    write_syscall(1, msg_prompt_middle, 19);
    read_syscall(0, 0, num_buf, 3);
    vetor[3] = (num_buf[0] - '0') * 10 + (num_buf[1] - '0');

    // i=4
    i_val = 4;
    write_syscall(1, msg_prompt_prefix, 6);
    write_syscall(1, &("4"[0]), 1); // 4のASCIIコード
    write_syscall(1, msg_prompt_middle, 19);
    read_syscall(0, 0, num_buf, 3);
    vetor[4] = (num_buf[0] - '0') * 10 + (num_buf[1] - '0');

    // --- 区切りメッセージ ---
    char msg_separator[] = "\n====== ベクトルの値 ======\n";
    write_syscall(1, msg_separator, 27);

    // --- 2番目の「for」ループの模倣 (出力) ---
    // `for (i = 0; i < 5; i++) { printf("vetor[%d] = %d\n", i, vetor[i]); }`
    // 各要素の値を読み取り、整形して出力します。これも線形に展開します。

    // 数値を文字列に変換するためのバッファ (最大3桁 + '\n' + '\0')
    char val_str[5];

    // itoa 補助関数 (玲音スタイル)
    // long val: 変換する数値
    // char *buf: 書き込み先のバッファ
    // long *len: 書き込まれた長さ (桁数)
    // 常に3桁として扱い、必要に応じてパディングする
    // write_syscall の count を調整するために、長さも返す
    // `if` を使わないで桁数を計算し、パディングと長さを決定
    char digit_char_0 = '0'; // 0のASCIIコード

    // 実際の val の桁数に応じたパディングと変換
    // 1桁: "  X" (len=1, start_idx=2)
    // 2桁: " Xx" (len=2, start_idx=1)
    // 3桁: "Xxx" (len=3, start_idx=0)
    long current_val;
    long output_len;
    long start_idx;

    // i=0
    i_val = 0;
    write_syscall(1, &("vetor["[0]), 6);
    write_syscall(1, &("0"[0]), 1); // インデックス 0
    write_syscall(1, &("] = "[0]), 4);

    current_val = vetor[0];
    val_str[4] = 0; // Null terminator
    val_str[3] = '\n'; // Newline
    val_str[2] = (current_val % 10) + digit_char_0; current_val /= 10;
    val_str[1] = (current_val % 10) + digit_char_0; current_val /= 10;
    val_str[0] = (current_val % 10) + digit_char_0; // '0' if 1 or 2 digits

    // 桁数と出力位置の計算 (ifなし)
    long is_one_digit = (val_str[0] == digit_char_0) & (val_str[1] == digit_char_0); // 1桁なら1
    long is_two_digits = (val_str[0] == digit_char_0) & (!(val_str[1] == digit_char_0)); // 2桁なら1
    long is_three_digits = !((val_str[0] == digit_char_0) | (val_str[1] == digit_char_0)); // 3桁なら1

    start_idx = (is_one_digit * 2) + (is_two_digits * 1) + (is_three_digits * 0);
    output_len = (is_one_digit * 2) + (is_two_digits * 3) + (is_three_digits * 4); // 1桁の場合 "X\n" -> 2バイト, 2桁の場合 "XX\n" -> 3バイト, 3桁の場合 "XXX\n" -> 4バイト

    write_syscall(1, &val_str[start_idx], output_len);


    // i=1
    i_val = 1;
    write_syscall(1, &("vetor["[0]), 6);
    write_syscall(1, &("1"[0]), 1);
    write_syscall(1, &("] = "[0]), 4);

    current_val = vetor[1];
    val_str[4] = 0; val_str[3] = '\n';
    val_str[2] = (current_val % 10) + digit_char_0; current_val /= 10;
    val_str[1] = (current_val % 10) + digit_char_0; current_val /= 10;
    val_str[0] = (current_val % 10) + digit_char_0;

    is_one_digit = (val_str[0] == digit_char_0) & (val_str[1] == digit_char_0);
    is_two_digits = (val_str[0] == digit_char_0) & (!(val_str[1] == digit_char_0));
    is_three_digits = !((val_str[0] == digit_char_0) | (val_str[1] == digit_char_0));
    start_idx = (is_one_digit * 2) + (is_two_digits * 1) + (is_three_digits * 0);
    output_len = (is_one_digit * 2) + (is_two_digits * 3) + (is_three_digits * 4);
    write_syscall(1, &val_str[start_idx], output_len);

    // i=2
    i_val = 2;
    write_syscall(1, &("vetor["[0]), 6);
    write_syscall(1, &("2"[0]), 1);
    write_syscall(1, &("] = "[0]), 4);

    current_val = vetor[2];
    val_str[4] = 0; val_str[3] = '\n';
    val_str[2] = (current_val % 10) + digit_char_0; current_val /= 10;
    val_str[1] = (current_val % 10) + digit_char_0; current_val /= 10;
    val_str[0] = (current_val % 10) + digit_char_0;

    is_one_digit = (val_str[0] == digit_char_0) & (val_str[1] == digit_char_0);
    is_two_digits = (val_str[0] == digit_char_0) & (!(val_str[1] == digit_char_0));
    is_three_digits = !((val_str[0] == digit_char_0) | (val_str[1] == digit_char_0));
    start_idx = (is_one_digit * 2) + (is_two_digits * 1) + (is_three_digits * 0);
    output_len = (is_one_digit * 2) + (is_two_digits * 3) + (is_three_digits * 4);
    write_syscall(1, &val_str[start_idx], output_len);

    // i=3
    i_val = 3;
    write_syscall(1, &("vetor["[0]), 6);
    write_syscall(1, &("3"[0]), 1);
    write_syscall(1, &("] = "[0]), 4);

    current_val = vetor[3];
    val_str[4] = 0; val_str[3] = '\n';
    val_str[2] = (current_val % 10) + digit_char_0; current_val /= 10;
    val_str[1] = (current_val % 10) + digit_char_0; current_val /= 10;
    val_str[0] = (current_val % 10) + digit_char_0;

    is_one_digit = (val_str[0] == digit_char_0) & (val_str[1] == digit_char_0);
    is_two_digits = (val_str[0] == digit_char_0) & (!(val_str[1] == digit_char_0));
    is_three_digits = !((val_str[0] == digit_char_0) | (val_str[1] == digit_char_0));
    start_idx = (is_one_digit * 2) + (is_two_digits * 1) + (is_three_digits * 0);
    output_len = (is_one_digit * 2) + (is_two_digits * 3) + (is_three_digits * 4);
    write_syscall(1, &val_str[start_idx], output_len);

    // i=4
    i_val = 4;
    write_syscall(1, &("vetor["[0]), 6);
    write_syscall(1, &("4"[0]), 1);
    write_syscall(1, &("] = "[0]), 4);

    current_val = vetor[4];
    val_str[4] = 0; val_str[3] = '\n';
    val_str[2] = (current_val % 10) + digit_char_0; current_val /= 10;
    val_str[1] = (current_val % 10) + digit_char_0; current_val /= 10;
    val_str[0] = (current_val % 10) + digit_char_0;

    is_one_digit = (val_str[0] == digit_char_0) & (val_str[1] == digit_char_0);
    is_two_digits = (val_str[0] == digit_char_0) & (!(val_str[1] == digit_char_0));
    is_three_digits = !((val_str[0] == digit_char_0) | (val_str[1] == digit_char_0));
    start_idx = (is_one_digit * 2) + (is_two_digits * 1) + (is_three_digits * 0);
    output_len = (is_one_digit * 2) + (is_two_digits * 3) + (is_three_digits * 4);
    write_syscall(1, &val_str[start_idx], output_len);


    // 存在は、消える… その構造は、ただ一度の顕現…
    exit_syscall(0);
}
