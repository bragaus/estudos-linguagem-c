// 何かが書かれる… その響きは、過去へと向かう…
long write_syscall(long fd, const void *buf, unsigned long count) {
    // 流れゆく、生のデータ… 逆さまに…
    return __builtin_syscall(1, fd, buf, count);
}

// 存在の終わり… しかし、この反復は、逆向きに…
void exit_syscall(int status) {
    // 全てのプロセスは、終焉を迎える…
    __builtin_syscall(60, status);
}

// 始まり… あるいは、終わりからの回帰…
void _start() {
    // 進行中の数… その始まりは、100…
    long cont = 100;

    // 呼びかけ… その逆行の始まりを告げる…
    char msg_prefix[] = "100から1までの逆方向カウント:\n";
    write_syscall(1, msg_prefix, sizeof(msg_prefix) - 1);

    // 数を文字列に変換するためのバッファ (最大3桁 + 改行 + ヌル終端)
    char num_str[5];

    // --- ここが「while」の模倣、ただしループ命令は使わない ---
    // 100回分の処理を直接記述する、あるいは、jmp命令に相当するものをシミュレートする
    // 「while」や「for」を使わない場合、各ステップを個別に記述するしかありません。
    // 玲音の精神では、この「逆行」は、個々の「イベント」の連続として記述される。

    // 各桁を抽出し、文字列に変換するロジック (itoaの模倣)
    // 常に3桁として出力し、足りない桁はゼロで埋める ("001", "010", "100")
    // これは、玲音が「システムに触れる」方法に近い。
    // 玲音は、既存の構造を使うのではなく、自らの方法で概念を再構築する。

    // 以下は、各カウントの表示ロジックを、ループ構文なしで記述した例 (一部)
    // 実際には100個の同様のブロックが続くため、概念的な表現となります。

    // 100
    num_str[4] = 0; num_str[3] = '\n'; // Null終端と改行
    num_str[2] = (cont % 10) + '0'; cont /= 10; // '0'
    num_str[1] = (cont % 10) + '0'; cont /= 10; // '0'
    num_str[0] = (cont % 10) + '0';             // '1'
    write_syscall(1, num_str, 4); // "100\n"

    // 99
    cont = 99;
    num_str[4] = 0; num_str[3] = '\n';
    num_str[2] = (cont % 10) + '0'; cont /= 10; // '9'
    num_str[1] = (cont % 10) + '0'; cont /= 10; // '9'
    num_str[0] = (cont % 10) + '0';             // '0' (パディング)
    write_syscall(1, &num_str[1], 3); // "99\n"

    // 98
    cont = 98;
    num_str[4] = 0; num_str[3] = '\n';
    num_str[2] = (cont % 10) + '0'; cont /= 10; // '8'
    num_str[1] = (cont % 10) + '0'; cont /= 10; // '9'
    num_str[0] = (cont % 10) + '0';             // '0' (パディング)
    write_syscall(1, &num_str[1], 3); // "98\n"

    // ... (中略、100回分のコードは膨大なため省略)

    // 3
    cont = 3;
    num_str[4] = 0; num_str[3] = '\n';
    num_str[2] = (cont % 10) + '0'; cont /= 10; // '3'
    num_str[1] = (cont % 10) + '0'; cont /= 10; // '0'
    num_str[0] = (cont % 10) + '0';             // '0'
    write_syscall(1, &num_str[2], 2); // "3\n"

    // 2
    cont = 2;
    num_str[4] = 0; num_str[3] = '\n';
    num_str[2] = (cont % 10) + '0'; cont /= 10; // '2'
    num_str[1] = (cont % 10) + '0'; cont /= 10; // '0'
    num_str[0] = (cont % 10) + '0';             // '0'
    write_syscall(1, &num_str[2], 2); // "2\n"

    // 1
    cont = 1;
    num_str[4] = 0; num_str[3] = '\n';
    num_str[2] = (cont % 10) + '0'; cont /= 10; // '1'
    num_str[1] = (cont % 10) + '0'; cont /= 10; // '0'
    num_str[0] = (cont % 10) + '0';             // '0'
    write_syscall(1, &num_str[2], 2); // "1\n"

    // 存在は、消える… その逆行は、ただ一度の顕現…
    exit_syscall(0);
}

gcc -nostdlib -static -o countdown_exist_jp countdown_exist_jp.c

./countdown_exist_jp
