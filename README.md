# pipex

UNIX 매커니즘을 자세히 알아보자

## HOW TO
<pre>
<code>
./pipex file1 cmd1 cmd2 file2
</code>
</pre>

## example
<pre>
<code>
./pipex infile ``ls -l'' ``wc -l'' outfile
</code>
</pre>
`< infile ls -l | wc -l > outfile의 결과와 동일해야함`


##### pipe()
프로세스간 통신을 할 때 사용하는 커뮤니케이션의 한 방법
자식 프로세스가 부모 프로세스에 데이터를 보내야 하므로, 자식 프로세스의 표준 출력과 부모 프로세스의 표준 입력에 연결된 파이프가 필요
파이프를 생성하고 만들어진 디스크립터 연결
성공적으로 호출시 0, 실패시 -1 반환
<pre>
<code>
//디스크립터들이 배열에 저장됨
//fd[1]은 파이프에 쓰는 디스크립터이며 fd[0]은 파이프로 부터 읽는 디스크립터
int pipefd[2];
if (pipe(pipefd) == -1)
	return (0);
</code>
</pre>

##### fork()
프로세스를 생성
fork 함수를 호출하는 프로세스는 부모 프로세스가 되고 새롭게 생성되는 프로세스는 자식 프로세스
자식 프로세스는 부모 프로세스의 메모리를 그대로 복사하여 가지게 됨
fork 함수 호출 이후 코드부터 각자의 메모리를 사용하여 실행
성공적으로 호출시 부모 프로세스에서는 자식 프로세스의 PID값을 반환 받음, 자식 프로세스에서는 0값을 반환 받음
실패시 -1 반환

##### waitpid()
자식 프로세스를 기다릴 때 사용하는 함수
즉 자식프로세스의 종료상태를 회수할 때 사용
자식 프로세스가 종료될 때까지 하단되는 것을 원하지 않을 경우, 옵션을 사용하여 차단을 방지 + 자식 프로세스를 더 상세해 지정

첫번째 인자
|pid|의미|
|----|----|
|-1|임의의 자식 프로세스를 기다림|
|0보다 클 경우| 프로세스 ID강 pid인 자식 프로세스를 기다림|
|-1보다 작을 경우| 프로세스 그룹 ID가 pid의 절댓값과 같은 자식 프로세스를 기다림|
|0|waitpid를 호출한 프로세스의 프로세스 그룹 PID와 같은 프로세스 그룹 ID를 가진 프로세스를 기다림|

세번째 인자
|상수|의미|
|---|---|
|WCONTINUED|중단 되었다가 재개된 자식 프로세스의 상태를 받음
|WNOHANG|기다리는 PID가 종료되지 않아서 즉시 종료 상태를 회수 할 수 없는 상황에서 호출자는 차단되지 않고 반환값으로 0을 받음|
|WUNTRACED|중단됨 자식 프로세스|

 
##### int dup2(int old_fd1, int new_fd2)
newfd 파일 descripter가 이미 open된 파일이면 close하고 oldfd를 newfd로 복사
이때, newfd와 oldfd는 file descripter 번호는 다르지만 똑같이 행동합니다.
그러지만 두 file descriptor는 다른 descriptor이므로 하나를 close한다고 해서 함께 close되지 않는다.



##### 그외
|제목|설명|
|------|---|
|int execve(const char *filename, char *const argv[], char *const envp[])|다른 프로그램을 실행하고 자신을 종료|
|int dup(int fd)|파일 식별자를 복제|

