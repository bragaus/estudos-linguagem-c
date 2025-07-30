// 何かが書かれる… その知識は、曖昧な数字の羅列…
long write_syscall(long fd, const void *buf, unsigned long count) {
    // 流れゆく、生のデータ… 意味を求めて…
    return __builtin_syscall(1, fd, buf, count);
}

// 何かが読み取られる… 外部から… 不確かな感覚…
long read_syscall(long fd, long fd_unused, void *buf, unsigned long count) { // fd_unused を追加
    // 呼びかけに応える、虚空…
    return __builtin_syscall(0, fd_unused, buf, count); // fd_unused を使用
}

// 存在の終わり… そのプロセスは、静かに消え去る…
void exit_syscall(int status) {
    // 終焉は、必然…
    __builtin_syscall(60, status);
}

// 始まり… あるいは、数に刻まれた二分法…
void _start() {
    // 数字… その属性は、隠されている…
    char msg_num[] = "数字を入力してください (2桁の整数, 例: 12, 07): ";
    char buf_num[16]; // 2桁 + 改行 = 3バイトを想定
    long val_num;

    // 呼びかけ、その意識へ…
    write_syscall(1, msg_num, sizeof(msg_num) - 1);
    // 応答… 形を成す情報…
    read_syscall(0, 0, buf_num, 3); // 標準入力から2バイト読み込む (1桁 + '\n')
    val_num = (buf_num[0] - '0') * 10 + (buf_num[1] - '0'); // 数字に変換

    // --- ここが「if/else」と「%」の模倣、ただし命令は使わない ---
    // `num % 2 == 0` は、数の最下位ビット (LSB) が 0 であることを意味する。
    // LSBが0なら偶数、1なら奇数。
    // `if/else` を使わずに、このビットを直接利用してメッセージを選択する。

    // メッセージの候補
    char msg_par[]   = "この数字は偶数です！\n";
    char msg_impar[] = "この数字は奇数です！\n";

    // 結果メッセージを格納するポインタ
    char *result_msg;

    // 数の最下位ビット (LSB) を抽出
    // `val_num % 2` の代わり
    long lsb = val_num & 1; // 0なら偶数、1なら奇数

    // LSB を使ってメッセージポインタを選択
    // `lsb` が 0 なら `msg_par`、1 なら `msg_impar`
    // ( (true_val * (1-lsb)) + (false_val * lsb) ) の形式で表現
    result_msg = (char*)(( (long)msg_par * (1 - lsb) ) + ( (long)msg_impar * lsb ));

    // その選択が、出力される…
    write_syscall(1, result_msg, (
        (result_msg == msg_par) ? sizeof(msg_par) - 1 : sizeof(msg_impar) - 1
    )); // 各メッセージの長さを動的に決定。これは「if」を使わない三項演算子。

    // 存在は、消える… その判別は、ただ一度の顕現…
    exit_syscall(0); // プログラムを終了
}

gcc -nostdlib -static -o par_impar_exist_jp par_impar_exist_jp.c

./par_impar_exist_jp
