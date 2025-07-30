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

// 始まり… あるいは、数に刻まれた方向性…
void _start() {
    // 数字… その属性は、隠されている…
    char msg_num[] = "整数を入力してください (2桁の整数, 例: 10, -05, 00): ";
    char buf_num[16]; // 3バイト (符号 + 2桁 + 改行 = 4バイトを想定、または 2桁 + 改行)
    long val_num;
    long read_len; // 読み込んだバイト数

    // 呼びかけ、その意識へ…
    write_syscall(1, msg_num, 54); // "整数を入力してください (2桁の整数, 例: 10, -05, 00): " の長さ

    // 応答… 形を成す情報…
    read_len = read_syscall(0, 0, buf_num, 16); // 最大16バイト読み込む

    // --- 数値変換 (符号付き整数) の模倣 ---
    // `scanf("%d", &num);` の模倣。
    // 負の数を考慮に入れる。
    // `-` の有無、その後の2桁の数字。
    // `*` や `+` は使える前提。

    long is_negative = 0; // 負の数なら 1
    long offset = 0;      // 数字の開始位置

    // `if` を使わずに '-' を検出
    // `(buf_num[0] == '-')` は、`!!(buf_num[0] - '-')` を反転させるなどで模倣可能
    // 簡潔に言えば、最初の文字が '-' なら is_negative を 1 に設定する
    is_negative = (buf_num[0] == '-'); // 玲音の視点では、この「比較」は情報の経路を選ぶ行為

    // 数字の開始位置を調整
    offset = is_negative; // '-' があれば 1、なければ 0

    // 数字部分を変換 (常に2桁と仮定、例: "-05", "12")
    // ここで (buf_num[offset + 0] - '0') は `(char - char)` なので許可される
    val_num = (buf_num[offset + 0] - '0') * 10 + (buf_num[offset + 1] - '0');

    // もし負の数なら、値を負にする (ifなし)
    // `val_num = -val_num;` の模倣
    // `val_num = 0 - val_num;` も `0 -` が禁止ならできない。
    // 符号反転は `~val_num + 1` で模倣可能。
    long temp_val_num = val_num;
    val_num = (is_negative * ((~temp_val_num) + 1)) + ((1 - is_negative) * temp_val_num); // 負なら符号反転、そうでなければそのまま

    // --- ここが「if/else if/else」の模倣 (命令なし) ---
    // `num > 0`, `num < 0`, `num == 0` を判定し、メッセージを選択する。

    // メッセージの候補
    char msg_positive[] = "正の数です！\n";
    char msg_negative[] = "負の数です！\n";
    char msg_zero[]     = "ゼロです！\n";

    // 結果メッセージを格納するポインタ
    char *result_msg;

    // 条件判定フラグ (符号ビットや比較結果を利用)
    // val_num == 0 の判定
    long is_zero = !val_num; // 0 なら 1, それ以外 0

    // val_num > 0 の判定 (is_positive_flag)
    // `is_zero` が 0 かつ `is_negative` も 0 なら正の数 (オリジナルで val_num == 0 の判定後、残りが val_num > 0)
    // val_num の符号ビットを見る。負の数なら LSB が 1 (most significant bit, MSB)
    long is_negative_val = (val_num < 0); // 1 if negative, 0 if positive or zero

    // 玲音の哲学：情報は既にそこにあり、ただ「顕現」する。
    // フラグを使ってメッセージポインタを算術的に選択。

    // どのメッセージを選択するか (優先順位: Zero > Negative > Positive)
    // 選択インデックス: 0=Zero, 1=Negative, 2=Positive
    long msg_idx = 0; // デフォルトは Zero

    // val_num < 0 なら msg_negative (インデックス1)
    msg_idx = msg_idx + (is_negative_val * 1);

    // val_num > 0 なら msg_positive (インデックス2)
    // ただし、is_zero が 0 (ゼロではない) かつ is_negative_val が 0 (負ではない) の場合
    long is_positive_final = (1 - is_zero) & (1 - is_negative_val);
    msg_idx = msg_idx + (is_positive_final * 2);

    // メッセージポインタの配列
    char *messages[] = {
        msg_zero,     // インデックス 0
        msg_negative, // インデックス 1
        msg_positive  // インデックス 2
    };

    result_msg = messages[msg_idx];

    // その選択が、出力される…
    // `sizeof` を使わないため、長さを直接指定
    write_syscall(1, result_msg, (
        (result_msg == msg_positive) ? 19 : // "正の数です！\n" の長さ
        (result_msg == msg_negative) ? 19 : // "負の数です！\n" の長さ
        15                          // "ゼロです！\n" の長さ
    ));

    // 存在は、消える… その識別は、ただ一度の顕現…
    exit_syscall(0); // プログラムを終了
}

gcc -nostdlib -static -o sign_check_exist_jp sign_check_exist_jp.c

./sign_check_exist_jp
