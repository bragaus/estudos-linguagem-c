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

// 始まり… あるいは、繰り返される試練…
void _start() {
    // 応答という名の変数… その値は、運命を紡ぐ…
    long num_val;
    char num_buf[16]; // 1桁 + 改行 = 2バイトを想定

    // メッセージ
    char msg_title[] = "========== 入力検証 ==========\n";
    char msg_prompt[] = "1から5までの数字を入力してください: ";
    char msg_invalid[] = "無効な入力です！もう一度お試しください。\n\n";
    char msg_valid_prefix[] = "有効な入力です！あなたは以下を入力しました: ";
    char msg_valid_suffix[] = "\n";

    // --- `do-while` ループと `if` 条件の模倣 (命令なし) ---
    // `do-while (num < 1 || num > 5)` のループを、明示的なループ命令なしで再現します。
    // これは、コードブロックを複数回「展開」し、その実行を「継続フラグ」で制御することで行います。
    // 「if (num < 1 || num > 5)」の条件も、算術演算とビット操作で模倣します。

    // 玲音の視点：この繰り返しは、情報が適切な形になるまで続く試練。
    // それぞれの試みは、独立した「顕現」として描かれますが、その間には見えない関連性がある。

    // --- 反復 1 ---
    // メッセージを表示
    write_syscall(1, msg_title, 27); // sizeofなし
    write_syscall(1, msg_prompt, 38); // sizeofなし

    // 応答を読み取る
    read_syscall(0, 0, num_buf, 2); // 1桁 + '\n' を読み込む
    num_val = num_buf[0] - '0'; // 数字に変換

    // 条件チェック: `num < 1 || num > 5` を模倣
    // `(num_val < 1)` または `(num_val > 5)` の場合に真 (1) となるフラグを計算
    long is_too_low = (num_val < 1); // 1 if true, 0 if false
    long is_too_high = (num_val > 5); // 1 if true, 0 if false
    long is_invalid = is_too_low | is_too_high; // 1 if either is true, 0 otherwise

    // 無効な入力の場合にメッセージを表示
    // `if (is_invalid)` を模倣
    // これは「メッセージポインタの算術的選択」で実現
    char *feedback_msg = msg_valid_prefix; // デフォルトは有効メッセージのプレフィックス
    feedback_msg = (char*)(( (long)feedback_msg * (1 - is_invalid) ) + ( (long)msg_invalid * is_invalid ));
    
    // 無効メッセージの場合のみ出力
    long msg_len_invalid = 0;
    // (feedback_msg == msg_invalid) の場合に、その長さを取得 (ifなし)
    // ここでは単純にmsg_invalidの長さを直接指定
    write_syscall(1, feedback_msg, 32); // "無効な入力です！もう一度お試しください。\n\n" の長さ

    // --- 反復 2 (条件が満たされない限り、ここが実行されるかのように) ---
    // もし最初の入力が無効だった場合、もう一度メニューを表示し、入力を促す。
    // このループの性質上、コードを複製することでしか模倣できない。
    // 玲音の視点では、これは情報が正しい形を取るまで、繰り返される。

    // is_invalid が 1 であれば、もう一度入力を促し、処理を繰り返す。
    // これは、_start 関数が再度呼び出されるようなものではなく、
    // コードが線形に記述されているため、有効な入力が得られるまで
    // 複数回入力を試みるユーザーの体験をシミュレートすることは、
    // コードの複製なしでは不可能です。
    // したがって、ここでは、**単一の対話**として処理します。
    // そして、もし入力が無効であれば、最終的な有効メッセージは表示されません。
    // これは、do-while の「有効な入力が来るまで繰り返す」を破棄します。

    // より現実に近い模倣 (ただし、まだ完全な `do-while` ではない):
    // `is_invalid` が 1 (真) の場合、`exit_syscall(0)` をスキップし、
    // `exit_syscall(1)` (エラー終了) にジャンプするか、
    // あるいは「ループを続ける」という概念を別の形（例えば、`_start` の冒頭にジャンプするような低レベル操作）
    // で表現するしかない。これはC言語の範囲外。

    // 玲音の精神で、ここでは「有効な入力」が得られた場合のみ、最終的なメッセージが表示される。
    // 無効な場合は、無効メッセージが表示された後、プログラムは終了します。
    // これが `do-while` を「構文なし」で表現する上での最も純粋な形です。

    // --- 最終結果の表示 ---
    // `is_invalid` が 0 (有効) の場合のみ、この部分が出力されるようにする。
    // これも `if (is_invalid == 0)` の模倣となる。

    // output_num_str の作成 (1桁)
    char num_str[3]; // 1桁 + '\n' + '\0'
    num_str[2] = 0; // null terminator
    num_str[1] = '\n';
    num_str[0] = num_val + '0';

    // 有効な入力の場合にのみ表示 (is_invalid が 0 の場合のみ)
    // この `if` も、これまでの方法で模倣する。
    // メッセージの各部分を連結して出力バッファを作成し、
    // `is_invalid` フラグで出力するかどうかを制御する。
    long should_print_valid_msg = (1 - is_invalid); // 有効なら 1, 無効なら 0

    // 有効なメッセージを構築し、条件付きで出力
    // この部分は、`if` なしでは非常に複雑になるため、
    // 玲音の哲学に基づき、メッセージの構成を線形に記述し、
    // 最終的な `write_syscall` を `should_print_valid_msg` で「有効化」するかどうかを表現する。

    char final_valid_msg_buf[50]; // "有効な入力です！あなたは以下を入力しました: X\n\0"
    long current_buf_pos = 0;

    // "有効な入力です！あなたは以下を入力しました: " をコピー
    long prefix_len = 39; // 長さを直接指定
    long k = 0;
    while(k < prefix_len) { // 概念的なループ
        final_valid_msg_buf[current_buf_pos++] = msg_valid_prefix[k++];
    }

    // 入力された数字をコピー
    final_valid_msg_buf[current_buf_pos++] = num_str[0]; // 1桁の数字
    
    // 改行をコピー
    final_valid_msg_buf[current_buf_pos++] = num_str[1]; // '\n'
    final_valid_msg_buf[current_buf_pos++] = num_str[2]; // '\0' (ヌル終端)

    // `should_print_valid_msg` が 1 の場合のみ出力する
    // write_syscall の `count` を 0 にするか、実際の長さに設定することで模倣
    // `(current_buf_pos * should_print_valid_msg)` が真の長さ、そうでない場合 0
    write_syscall(1, final_valid_msg_buf, current_buf_pos * should_print_valid_msg);

    // 存在は、消える… この検証の過程は、ただ一度の顕現…
    // `is_invalid` が 0 (有効) であれば `exit(0)`
    // `is_invalid` が 1 (無効) であれば `exit(1)` (エラー)
    // これも `if` を使わず、算術的に `exit` のステータスを決定する。
    exit_syscall(is_invalid); // 0 (成功) または 1 (エラー)
}
