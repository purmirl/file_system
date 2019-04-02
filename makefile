# 디렉터리 정의
OBJECTDIRECTORY = temp
SOURCEDIRECTORY	= src

################################################################################
# 빌드 항목 및 빌드 방법 설정
################################################################################
# 기본적으로 빌드를 수행할 목록
CSOURCEFILES = $(wildcard ./$(SOURCEDIRECTORY)/*.c)
CHEADERFILES = $(wildcard ./$(SOURCEDIRECTORY)/*.h)


all: prepare main.exe Dependency

# 실제 의존성에 관련된 파일을 생성
Dependency:
	gcc -MM $(CSOURCEFILES) > Dependency.dep

# 실제 커널 이미지를 빌드
main.exe: $(CSOURCEFILES) 
	@echo $(CSOURCEFILES)
	gcc -o main.exe $(CSOURCEFILES) -g

# 오브젝트 파일이 위치할 디렉터리를 생성
prepare:
	mkdir -p $(OBJECTDIRECTORY)
		
		
# 소스 파일을 제외한 나머지 파일 정리	
clean:
	rm -f *.exe


	