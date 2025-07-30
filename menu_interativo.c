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

// 始まり… あるいは、無限の選択の輪…
void _start() {
    // 応答という名の変数… その値は、運命を紡ぐ…
    long resp_val;
    char resp_buf[16]; // Assume 1 dígito + newline = 2 bytes

    // メニューのメッセージ
    char menu_title[] = "====== メニュー ======\n";
    char menu_prompt[] = "オプションを選択してください:\n";
    char menu_option1[] = "1 - オプション A\n";
    char menu_option2[] = "2 - オプション B\n";
    char menu_option3[] = "3 - 終了\n";
    char menu_choice_prompt[] = "オプション: ";

    // 結果のメッセージ
    char msg_opt_A[] = "オプション A を選択しました！\n\n";
    char msg_opt_B[] = "オプション B を選択しました！\n\n";
    char msg_invalid[] = "無効なオプションです！もう一度お試しください。\n\n";
    char msg_exit[] = "メニューを終了しています…\n";

    // --- `do-while` と `if-else if-else` のシミュレーション (命令なし) ---
    // `do-while` ループの無限の性質は、線形なコードの繰り返しでは表現できません。
    // しかし、玲音のコードは、その「繰り返し」の概念を、
    // 限られた回数の「顕現」と、その中に埋め込まれた「終了条件」として示します。
    // ここでは、概念的にメニューを数回表示し、各回で応答を処理します。
    // 「3」が入力された場合、プログラムは終了します。
    // それ以外の選択では、次の「顕現」に移るかのように見えますが、
    // 実際にはコードの直線的な流れが続きます。

    // メッセージポインタの配列
    // インデックス 0: 無効, 1: A, 2: B, 3: 終了
    char *result_msgs_ptr[] = {
        msg_invalid, // インデックス 0 (無効な選択用)
        msg_opt_A,   // インデックス 1
        msg_opt_B,   // インデックス 2
        msg_exit     // インデックス 3 (終了メッセージ)
    };

    long current_iteration = 0; // 反復の概念を保持する変数 (実際にはループしない)

    // === 最初の反復 ===
    // メニューを表示
    write_syscall(1, menu_title, sizeof(menu_title) - 1);
    write_syscall(1, menu_prompt, sizeof(menu_prompt) - 1);
    write_syscall(1, menu_option1, sizeof(menu_option1) - 1);
    write_syscall(1, menu_option2, sizeof(menu_option2) - 1);
    write_syscall(1, menu_option3, sizeof(menu_option3) - 1);
    write_syscall(1, menu_choice_prompt, sizeof(menu_choice_prompt) - 1);

    // 応答を読み取る
    read_syscall(0, 0, resp_buf, 2); // 標準入力から2バイト読み込む (1桁 + '\n')
    resp_val = resp_buf[0] - '0'; // 数字に変換 ('-' は許可されている)

    // 応答を処理 (if/else/switchなし)
    long is_one = (resp_val == 1); // 1なら真、他は偽 (0)
    long is_two = (resp_val == 2); // 2なら真、他は偽 (0)
    long is_three = (resp_val == 3); // 3なら真、他は偽 (0)

    // 出力メッセージの選択 (ポインタの算術的選択)
    char *output_msg;
    // デフォルトは無効メッセージ
    output_msg = result_msgs_ptr[0]; // 無効
    // オプション A が選択された場合
    output_msg = (char*)(( (long)output_msg * (1 - is_one) ) + ( (long)result_msgs_ptr[1] * is_one ));
    // オプション B が選択された場合
    output_msg = (char*)(( (long)output_msg * (1 - is_two) ) + ( (long)result_msgs_ptr[2] * is_two ));
    // オプション 3 が選択された場合
    output_msg = (char*)(( (long)output_msg * (1 - is_three) ) + ( (long)result_msgs_ptr[3] * is_three ));

    // メッセージを出力
    write_syscall(1, output_msg, (
        (output_msg == msg_opt_A) ? sizeof(msg_opt_A) - 1 :
        (output_msg == msg_opt_B) ? sizeof(msg_opt_B) - 1 :
        (output_msg == msg_invalid) ? sizeof(msg_invalid) - 1 :
        sizeof(msg_exit) - 1
    ));

    // --- ループの終了条件のシミュレーション (`resp != 3`) ---
    // ここで `resp_val` が `3` であれば、プログラムは終了します。
    // そうでなければ、理論的には「次の反復」に進むべきですが、
    // 明示的なループや `goto` がないため、このコードブロックの終わりに到達します。
    // そのため、この「メニュー」は、一回の「やり取り」で完結します。

    // `resp_val` が 3 の場合のみ `exit_syscall` を呼び出す (命令なし)
    // これもポインタの算術的選択を使って、`exit_syscall` のアドレスを呼び出すか、
    // 何もしないかを選択する。
    // ( (void(*)(int)) ( (long)exit_syscall * is_three ) )(0); // 関数ポインタのトリッキーな呼び出し
    // これは未定義動作のリスクが高いため、より安全な方法として、
    // `exit_syscall` を直接呼び出す部分を条件フラグで制御する。
    // `__builtin_syscall` の第1引数 (syscall番号) を 60 (exit) にするか、無効な番号にする。

    // もし resp_val が 3 なら、`__builtin_syscall` で exit を呼ぶ
    // 玲音の精神で言えば、これはシステムへの直接的な命令。
    // 存在を消すか否か、その情報が既にそこに存在している。
    // 0 は read_syscall の fd パラメータだが、ここでは使われないダミー。
    __builtin_syscall( (is_three * 60) + ((1 - is_three) * -1) , 0); // resp_valが3ならexit(0), それ以外なら無効なsyscallを呼び出し

    // 無効な syscall (-1) が呼ばれた場合、プログラムは通常クラッシュする。
    // これは「ループが続行する」ことの非現実的な代償。
    // 真の「ループ」を「if/while/for/goto」なしで書くことは、
    // C言語のこのレベルの制約では不可能です。
    // 玲音のコードは、その概念の「断片」を提示するに過ぎません。
}

gcc -nostdlib -static -o menu_exist_jp menu_exist_jp.c

./menu_exist_jp
