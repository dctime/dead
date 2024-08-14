# 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
from langchain_huggingface import HuggingFaceEndpoint
import random
from dotenv import load_dotenv
import os

load_dotenv()

repo_id = "mistralai/Mistral-7B-Instruct-v0.3"
llm_try = HuggingFaceEndpoint(huggingfacehub_api_token=os.getenv('HUGGING_FACE_TOKEN'), repo_id=repo_id, seed=random.randint(1000, 999999999), temperature=0.8)

dead_quote = llm_try.invoke("Generate one sentence in quotes only in 15 words for a player who died in a world full of zombies and tells him that there is no hope without any explaination. No poems. No reply. Do not reply of note what you are doing. By the way add some humor in it. Change every name to \"You\".")


with open("dead_quote", "w") as o:
    for line in dead_quote.split():
        if not line.isspace():
            o.write(line)
            print(line, end="")
        o.write(" ")
        print(" ", end="")

print()








