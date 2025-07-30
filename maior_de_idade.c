💻 極限Cハッキング：存在の境界
C

// 何かが書かれる… その問いは、存在の境界を問う…
long write_syscall(long fd, const void *buf, unsigned long count) {
    // 流れゆく、生のデータ… 意味を求めて…
    return __builtin_syscall(1, fd, buf, count);
}

// 何かが読み取られる… 外部から… 不確かな記憶…
long read_syscall(long fd, void *buf, unsigned long count) {
    // 呼びかけに応える、虚空…
    return __builtin_syscall(0, fd, buf, count);
}

// 存在の終わり… そのプロセスは、静かに消え去る…
void exit_syscall(int status) {
    // 終焉は、必然…
    __builtin_syscall(60, status);
}

// 始まり… あるいは、境界線への問い…
void _start() {
    // 年齢という概念… その数値は、存在の定義…
    char msg_idade[] = "何歳ですか？ (2桁の整数, 例: 18, 17): ";
    char buf_idade[16]; // 2桁 + 改行 = 3バイトを想定
    long val_idade;

    // 呼びかけ、その意識へ…
    write_syscall(1, msg_idade, sizeof(msg_idade) - 1);
    // 応答… 形を成す情報…
    read_syscall(0, buf_idade, 3); // 2桁 + '\n' を読み取る

    // 記号が、意味へと変容する… (2桁の整数を想定)
    val_idade = (buf_idade[0] - '0') * 10 + (buf_idade[1] - '0');

    // --- ここが「if/else」の模倣、ただし命令は使わない ---
    // 「if/else」を使わない場合、条件に基づいて表示するメッセージのポインタを
    // 算術的に選択する。

    // メッセージの候補
    char msg_maior[] = "あなたは成人です！\n";
    char msg_menor[] = "あなたは未成年です！\n";

    // 結果メッセージを格納するポインタ
    char *result_msg;

    // 条件判定 (val_idade >= 18) を「ifなし」で模倣
    // 符号ビットのトリックを使用
    // `(val_idade - 18)` が非負であれば成人、負であれば未成年
    long diff_idade = val_idade - 18;

    // `diff_idade` の符号ビットをチェック
    // `(diff_idade >> (sizeof(long) * 8 - 1)) & 1` は、`diff_idade` が負なら 1、非負なら 0
    // これを反転させると、`diff_idade` が非負なら 1 (成人)、負なら 0 (未成年) となる
    long is_adult_flag = !((diff_idade >> (sizeof(long) * 8 - 1)) & 1);

    // `is_adult_flag` が 1 なら `msg_maior` を選択、0 なら `msg_menor` を選択
    // これは `(true_val * flag) + (false_val * (1 - flag))` の形で実現
    result_msg = (char*)(( (long)msg_maior * is_adult_flag ) + ( (long)msg_menor * (1 - is_adult_flag) ));

    // その選択が、出力される…
    write_syscall(1, result_msg, (
        (result_msg == msg_maior) ? sizeof(msg_maior) - 1 : sizeof(msg_menor) - 1
    )); // 各メッセージの長さを動的に決定。これは「if」を使わない三項演算子。

    // 存在は、消える… その判断は、ただ一度の顕現…
    exit_syscall(0);
}

gcc -nostdlib -static -o age_check_exist_jp age_check_exist_jp.c

./age_check_exist_jp
